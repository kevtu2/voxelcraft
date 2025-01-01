#include "Application.hpp"
#include "Shader.hpp"
#include "blocks\BlockMesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"


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

	glViewport(0, 0, width, height);
	// Allow dynamic resizing of viewport
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glEnable(GL_DEPTH_TEST);
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
}


void Application::Run()
{
	VertexArray va_Block;

	VertexBuffer vb_Block(BLOCK_VERTEX_DATA, sizeof(BLOCK_VERTEX_DATA));
	IndexBuffer ib_Block(BLOCK_VERTEX_INDICES, sizeof(BLOCK_VERTEX_INDICES));

	va_Block.BindVertexBuffer(vb_Block, 0);

	Shader shaderProgram("../src/graphics/shader.vert", "../src/graphics/shader.frag");

	shaderProgram.UseProgram();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shaderProgram.SetUniformMatrix4f("model", model);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	view = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shaderProgram.SetUniformMatrix4f("view", view);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	shaderProgram.SetUniformMatrix4f("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ProcessInput();

		// Render
		Renderer::Draw(va_Block, ib_Block, shaderProgram);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
