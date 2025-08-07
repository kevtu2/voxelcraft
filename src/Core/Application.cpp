#include "Application.hpp"

#include <iostream>

#include "Graphics/VoxelShader.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/LightSource.hpp"

#include "Physics/Physics.hpp"

#include <imgui_impl_glfw.h>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Application::Application()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the main application window
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	float xScale, yScale;
	glfwGetMonitorContentScale(primaryMonitor, &xScale, &yScale);
	float dpiScale = xScale;

	width = mode->width / dpiScale;
	height = mode->height / dpiScale;

	std::cout << "Width: " << width << " Height: " << height << std::endl; 

	mouseX = width / 2;
	mouseY = height / 2;

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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);

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
	uiManager = std::make_unique<UIManager>(gameState);
	uiManager->uiState.monitorWidth = width;
	uiManager->uiState.monitorHeight = height;

	// Set up shaders
	shaderProgram = std::make_unique<VoxelShader>("../src/Graphics/shader.vert", "../src/Graphics/shader.frag");
	shaderProgram->UseProgram();
}

Application::~Application()
{
	if (window != NULL)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();

	delete mainLoopWorker;
	delete updateChunksWorker;
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

void Application::ProcessInput()
{
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
}

void Application::Run()
{
	mainLoopWorker = new std::thread(MainLoop);
	updateChunksWorker = new std::thread(Renderer::DrawChunk, )
}

void Application::MainLoop()
{
	VoxelShader crosshairShader("../src/Graphics/crosshair.vert", "../src/Graphics/crosshair.frag");

	// Set camera origin
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	shaderProgram->SetUniformMatrix4f("model", model);

	// Set up light source and textures
	LightSource light;
	Texture textureAtlas("../textures/blocks.png");

	// Hello new world!
	world = std::shared_ptr<World>(new World());

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!uiManager->ShouldShowTitleScreen())
		{
			shaderProgram->SetUniformMatrix4f("projection", player->GetProjectionMatrix());

			float currentTime = glfwGetTime();
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
			deltaTime = glm::clamp(deltaTime, 0.0f, 0.05f);
			gameState.deltaTime = deltaTime;

			/* --- Draw 3D world--- */
			shaderProgram->UseProgram();

			if (!uiManager->GameShouldPause())
			{
				CalculateNewMousePosition();
				ProcessInput();

				// Physics calculations
				Physics::CalculateGravity(player, deltaTime);
				Physics::CheckCollisions(player, world, deltaTime);
				player->Move(deltaTime);
				glm::vec3 pos = player->GetPlayerPosition();

				shaderProgram->SetUniformMatrix4f("view", player->GetViewMatrix());
				shaderProgram->SetUniformVec3f("cameraPosition", player->GetPlayerPosition());

				glm::vec3 cameraPos = player->GetPlayerPosition();
				light.SetLightPosition(cameraPos);
				shaderProgram->UseLightSource(light);

				/* --- Enable Draw Crosshair --- */
				crosshairShader.UseProgram();
				crosshairShader.SetUniformMatrix4f("projection", uiManager->GetHUDProjectionMat());
				crosshairShader.SetUniformVec2f("translation", glm::vec2(width / 2, height / 2));
			}
		}

		// ImGui and UI drawing
		imgui->StartGuiFrame();
		uiManager->DrawComponents();
		imgui->Render();

		ApplyGameState();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::ApplyGameState()
{
	world->setRenderDistance(gameState.renderDistance);
	player->SetFOV(gameState.FOV);
	player->SetMouseSensitivity(gameState.mouseSensitivity);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	std::shared_ptr<Player> player = app->GetPlayer();
	UIManager& uiManager = app->GetUIManager();

	if (!app)
	{
		std::cerr << "Could not find Application via GLFW Window User Pointer." << std::endl;
		exit(-1);
	}
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !uiManager.ShouldShowTitleScreen())
	{
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
