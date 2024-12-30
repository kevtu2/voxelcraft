#pragma once

#include <glad\glad.h>

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

};