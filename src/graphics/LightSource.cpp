#include "LightSource.hpp"

LightSource::LightSource() :
	lightColor(glm::vec3(0.5f, 0.5f, 0.5f)),
	lightPosition(glm::vec3(0.f, 250.f, 0.f))
{
	
}

void LightSource::SetLightColor(const glm::vec3& color)
{
	lightColor = color;
}

void LightSource::SetLightPosition(const glm::vec3& position)
{
	lightPosition.x = position.x;
	lightPosition.z = position.z;
}



