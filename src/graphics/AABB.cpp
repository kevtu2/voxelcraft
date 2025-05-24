#include "AABB.hpp"

AABB::AABB(const glm::vec3& position, unsigned int size) :
	position(position),
	height(size),
	width(size)
{
}

AABB::AABB(const glm::vec3& position, unsigned int height, unsigned int width) :
	position(position),
	height(height),
	width(width)
{
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->position = position - glm::vec3(-0.5f, 1.0f, -0.5f);
}
