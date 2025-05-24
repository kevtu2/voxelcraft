#include "AABB.hpp"

AABB::AABB(const glm::vec3& position, unsigned int size) :
	position(position + AABB_POS_OFFSET),
	height(size),
	width(size)
{
}

AABB::AABB(const glm::vec3& position, unsigned int height, unsigned int width) :
	position(position + AABB_POS_OFFSET),
	height(height),
	width(width)
{
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->position = position + AABB_POS_OFFSET;
}
