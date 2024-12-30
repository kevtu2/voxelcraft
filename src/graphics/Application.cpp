#include "Application.hpp"
#include "Shader.hpp"

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

}

Application::~Application()
{
	if (window != NULL)
	{
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

void Application::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


void Application::run()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};

	/*const char* vertexSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos, 1.0f);\n"
		"}\0";

	const char* fragmentSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n\0";*/

	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*unsigned int shaderProgram, vShader, fShader;
	shaderProgram = glCreateProgram();
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vertexSource, NULL);
	glCompileShader(vShader);

	glShaderSource(fShader, 1, &fragmentSource, NULL);
	glCompileShader(fShader);

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);*/

	Shader shaderProgram("shader.vert", "shader.frag");


	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput();

		// Render
		shaderProgram.useProgram();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}
}
