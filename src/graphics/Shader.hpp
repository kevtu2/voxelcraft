#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>


class Shader 
{
private:
	unsigned int programID;

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void useProgram();

	unsigned int getID() const { return programID; }
	
	void setUniformMatrix4f(const char* name, const glm::mat4 value);
};