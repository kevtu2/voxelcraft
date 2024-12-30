#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	programID = glCreateProgram();

	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vertFile;
	std::ifstream fragFile;

	// Allow exceptions to be thrown
	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		// Open and read shader programs
		vertFile.open(vertexPath);
		fragFile.open(fragmentPath);

		std::stringstream vertStream, fragStream;
		vertStream << vertFile.rdbuf();
		fragStream << fragFile.rdbuf();

		vertexSource = vertStream.str();
		fragmentSource = fragStream.str();

		vertFile.close();
		fragFile.close();
	}
	catch (const std::ifstream::failure& e) 
	{
		std::cerr << "Failed to read shader file: " << e.what() << std::endl;
		if (vertFile.is_open())
			vertFile.close();
		if (fragFile.is_open())
			fragFile.close();
		exit(-1);
	}

	// OpenGL expects a c-string as input
	const char* vertexSourceCode = vertexSource.c_str();
	const char* fragmentSourceCode = fragmentSource.c_str();

	// Create shaders and shader programs
	unsigned int vShader, fShader;

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexSourceCode, NULL);
	glCompileShader(vShader);

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentSourceCode, NULL);
	glCompileShader(fShader);

	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{
	if (programID)
	{
		glDeleteProgram(programID);
	}
}

void Shader::useProgram()
{
	glUseProgram(programID);
}