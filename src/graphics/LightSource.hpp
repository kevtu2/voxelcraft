#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#define AMBIENT 0.125f
#define SPECULAR 2.f

class LightSource
{
public:
	LightSource();
	glm::vec3 GetLightColor() const { return lightColor; }
	glm::vec3 GetLightPosition() const { return lightPosition; }
	void SetLightColor(const glm::vec3& color);
	void SetLightPosition(const glm::vec3& position);

private:
	glm::vec3 lightColor;
	glm::vec3 lightPosition;
};