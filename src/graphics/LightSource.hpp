#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#define AMBIENT 0.125f
#define SPECULAR 2.f

class LightSource
{
public:
	LightSource();
	~LightSource();

private:
	unsigned int lightVAO;
	unsigned int lightVBO;

};