#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#define AMBIENT 1.f
#define SPECULAR 16.f

class LightSource
{
public:
	LightSource();
	~LightSource();

private:
	unsigned int lightVAO;
	unsigned int lightVBO;

};