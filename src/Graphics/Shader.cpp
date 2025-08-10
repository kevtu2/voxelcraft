#include "Shader.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

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
	CheckShaderCompileErrors(vShader);

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentSourceCode, NULL);
	glCompileShader(fShader);
	CheckShaderCompileErrors(fShader);

	glAttachShader(programID, vShader);
	glAttachShader(programID, fShader);
	glLinkProgram(programID);

	// Check linking errors
	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
		exit(-1);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::CheckShaderCompileErrors(unsigned int shader)
{
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		std::string infoLog(logLength, ' ');
		glGetShaderInfoLog(shader, logLength, nullptr, &infoLog[0]);

		std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
		exit(-1);
	}
}

void Shader::UseProgram() const
{
	glUseProgram(programID);
}

void Shader::SetUniformMatrix4f(const char* name, const glm::mat4 value)
{
	int location = glGetUniformLocation(programID, name);
	if (location == -1)
	{
		std::cerr << "Uniform with name '" << name << "'" << " not found." << std::endl;
		exit(-1);
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniformVec2f(const char* name, const glm::vec2 value)
{
	int location = glGetUniformLocation(programID, name);
	if (location == -1)
	{
		std::cerr << "Uniform with name '" << name << "'" << " not found." << std::endl;
		exit(-1);
	}
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniformVec3f(const char* name, const glm::vec3 value)
{
	int location = glGetUniformLocation(programID, name);
	if (location == -1)
	{
		std::cerr << "Uniform with name '" << name << "'" << " not found." << std::endl;
		exit(-1);
	}
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::SetUniform1f(const char* name, const float value)
{
	int location = glGetUniformLocation(programID, name);
	if (location == -1)
	{
		std::cerr << "Uniform with name '" << name << "'" << " not found." << std::endl;
		exit(-1);
	}
	glUniform1f(location, value);
}