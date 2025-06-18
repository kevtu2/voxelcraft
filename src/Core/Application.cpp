#include "Application.hpp"

#include <iostream>

#include "Graphics/VoxelShader.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Texture.hpp"
#include "World/Chunk.hpp"
#include "Graphics/LightSource.hpp"

Application::Application()
	: deltaTime(0.0f),
	lastTime(0.0f),
	firstMouseInput(true),
	lastX(400.0f),
	lastY(300.0f)
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

	window = glfwCreateWindow(width, height, "voxelcraft", NULL, NULL);
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

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	player = std::make_shared<Player>(width, height);
}

void Application::CalculateNewMousePosition()
{
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	if (firstMouseInput)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouseInput = false;
	}
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	// Assume player not moving initially
	if (player->GetVelocity() != glm::vec3(0.0f))
		player->SetVelocity(glm::vec3(0.0f));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player->HandleInputControls(C_FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player->HandleInputControls(C_LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player->HandleInputControls(C_BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player->HandleInputControls(C_RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		player->HandleInputControls(C_DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		player->HandleInputControls(C_UP, deltaTime);
}

void Application::Run()
{
	VoxelShader shaderProgram("../src/graphics/shader.vert", "../src/graphics/shader.frag");
	shaderProgram.UseProgram();
	shaderProgram.SetUniformMatrix4f("projection", player->GetProjectionMatrix());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	shaderProgram.SetUniformMatrix4f("model", model);

	LightSource light;

	Texture textureAtlas("../textures/blocks.png");

	std::shared_ptr<World> world(new World());

	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		Renderer::DrawChunk(world, shaderProgram, textureAtlas, *player.get());
		
		CalculateNewMousePosition();
		ProcessInput();
		Renderer::CheckCollisions(player, world, deltaTime);
		player->Move(deltaTime);

		shaderProgram.SetUniformMatrix4f("view", player->GetViewMatrix());
		shaderProgram.SetUniformVec3f("cameraPosition", player->GetPlayerPosition());

		glm::vec3 aabbPos = player->GetAABBCollision().GetMin();
		glm::vec3 pos = player->GetPlayerPosition();
		
		glm::vec3 cameraPos = player->GetPlayerPosition();
		light.SetLightPosition(cameraPos);
		shaderProgram.UseLightSource(light);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
