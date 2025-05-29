#include "AABB.hpp"

AABB::AABB(const glm::vec3& position, float size) :
	min(position + AABB_POS_OFFSET),
	height(size),
	width(size),
	max(min + glm::vec3(width, height, width))
{
}

AABB::AABB(const glm::vec3& position, float height, float width) :
	min(position + AABB_POS_OFFSET),
	height(height),
	width(width),
	max(min + glm::vec3(width, height, width))
{
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->min = position + AABB_POS_OFFSET;
	this->max = min + glm::vec3(width, height, width);
}
