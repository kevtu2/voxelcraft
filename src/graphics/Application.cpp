#include "Application.hpp"
#include <filesystem>

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
	}
}

Application::Application(int width, int height)
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
	window = glfwCreateWindow(width, height, "voxelworx", NULL, NULL);
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

	camera.UpdateCameraLookAt(deltaTime, xOffset, yOffset);
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.HandleInputControls(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.HandleInputControls(LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.HandleInputControls(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.HandleInputControls(RIGHT, deltaTime);
}

void Application::Run()
{
	Shader shaderProgram("../src/graphics/shader.vert", "../src/graphics/shader.frag");
	shaderProgram.UseProgram();
	shaderProgram.SetUniformMatrix4f("projection", camera.GetProjectionMatrix());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	shaderProgram.SetUniformMatrix4f("model", model);

	Texture textureAtlas("../textures/blocks.png");



	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ProcessInput();
		CalculateNewMousePosition();
		shaderProgram.SetUniformMatrix4f("view", camera.GetViewMatrix());
		Renderer::DrawChunk(shaderProgram, textureAtlas);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
