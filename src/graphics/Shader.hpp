#pragma once

#include <glad\glad.h>

#include <fstream>
#include <iostream>
#include <string>


class Shader 
{
private:
	unsigned int programID;

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void useProgram();

};