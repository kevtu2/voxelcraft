#include "Application.hpp"

#include <iostream>

#include "Graphics/VoxelShader.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/LightSource.hpp"

#include "Physics/Physics.hpp"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Application::Application()
	: deltaTime(0.0f),
	lastTime(0.0f),
	firstMouseInput(true),
	mouseX(400.0f),
	mouseY(300.0f)
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the main application window
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
	width = mode->width;
	height = mode->height;

	window = glfwCreateWindow(width, height, "voxelcraft", primaryMonitor, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	// Allow dynamic resizing of viewport
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetWindowUserPointer(window, this);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	player = std::make_shared<Player>(width, height);

	// Set up ImGui and UI
	imgui = std::make_shared<ImGuiDriver>(window);
	uiManager = std::make_unique<UIManager>();

}

void Application::CalculateNewMousePosition()
{
	if (overrideMouseCalculation)
	{
		overrideMouseCalculation = false;
		return;
	}
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	if (firstMouseInput)
	{
		mouseX = xPos;
		mouseY = yPos;
		firstMouseInput = false;
	}
	float xOffset = xPos - mouseX;
	float yOffset = mouseY - yPos;
	mouseX = xPos;
	mouseY = yPos;

	player->UpdatePlayerLookAt(deltaTime, xOffset, yOffset);
}

Application::~Application()
{
	if (window != NULL)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

void Application::ProcessInput()
{
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);*/

	// Assume player not moving initially
	if (player->GetVelocity() != glm::vec3(0.0f))
		player->SetVelocity(glm::vec3(0.0f, player->GetVelocity().y, 0.0f));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player->HandleInputControls(C_FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player->HandleInputControls(C_LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player->HandleInputControls(C_BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player->HandleInputControls(C_RIGHT, deltaTime);
	
	// Maybe used for freecam mode?
	/*if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		player->HandleInputControls(C_DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		player->HandleInputControls(C_UP, deltaTime);*/
}

void Application::Run()
{
	// Set up shaders
	VoxelShader shaderProgram("../src/Graphics/shader.vert", "../src/Graphics/shader.frag");
	shaderProgram.UseProgram();
	shaderProgram.SetUniformMatrix4f("projection", player->GetProjectionMatrix());

	VoxelShader crosshairShader("../src/Graphics/crosshair.vert", "../src/Graphics/crosshair.frag");

	// Set camera origin
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	shaderProgram.SetUniformMatrix4f("model", model);

	// Set up light source and textures
	LightSource light;
	Texture textureAtlas("../textures/blocks.png");

	// New world!
	std::shared_ptr<World> world(new World());
	
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		deltaTime = glm::clamp(deltaTime, 0.0f, 0.05f);

		/* --- Draw 3D world--- */
		shaderProgram.UseProgram();

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw world chunks
		Renderer::DrawChunk(world, shaderProgram, textureAtlas, *player.get());
		
		// Determine where the character wants to move before calculating physics
		if (!uiManager->ShouldShowMainMenu()) 
		{
			CalculateNewMousePosition();
			ProcessInput();

			// Physics calculations
			Physics::CalculateGravity(player, deltaTime);
			Physics::CheckCollisions(player, world, deltaTime);
			player->Move(deltaTime);

			shaderProgram.SetUniformMatrix4f("view", player->GetViewMatrix());
			shaderProgram.SetUniformVec3f("cameraPosition", player->GetPlayerPosition());

			glm::vec3 cameraPos = player->GetPlayerPosition();
			light.SetLightPosition(cameraPos);
			shaderProgram.UseLightSource(light);

			/* --- Enable Draw Crosshair --- */
			crosshairShader.UseProgram();
			crosshairShader.SetUniformMatrix4f("projection", uiManager->GetHUDProjectionMat());
			crosshairShader.SetUniformVec2f("translation", glm::vec2(width / 2, height / 2));
		}
		
		// ImGui and UI drawing
		imgui->StartGuiFrame();
		uiManager->DrawComponents();
		imgui->Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	std::shared_ptr<Player> player = app->GetPlayer();

	if (!app)
	{
		std::cerr << "Could not find Application via GLFW Window User Pointer." << std::endl;
		exit(-1);
	}
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		UIManager& uiManager = app->GetUIManager();
		// Update main menu state
		bool showMainMenu = uiManager.ShouldShowMainMenu() ? false : true;
		uiManager.ToggleMainMenu(showMainMenu);

		// Change mouse settings after determining if main menu should show
		if (showMainMenu)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			app->overrideMouseCalculation = true;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		glm::vec2 windowDim = app->GetWindowDimensions();
		glfwSetCursorPos(window, windowDim.x / 2, windowDim.y / 2);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		player->HandleInputControls(C_JUMP, app->GetWorldDeltaTime());
	}
}