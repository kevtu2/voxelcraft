#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource();
	~LightSource();

private:
	unsigned int lightVAO;
	unsigned int lightVBO;

};