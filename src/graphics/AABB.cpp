#include "AABB.hpp"

AABB::AABB(const glm::vec3& position, float size) :
	min(position + AABB_POS_OFFSET),
	height(size),
	width(size),
	max(min + glm::vec3(width, height, width)),
	pos(glm::vec3((max.x + min.x)/2, min.y, (max.z + min.z) / 2)) // Bottom middle of the box
{
}

AABB::AABB(const glm::vec3& position, float height, float width) :
	min(position + AABB_POS_OFFSET),
	height(height),
	width(width),
	max(min + glm::vec3(width, height, width)),
	pos(glm::vec3((max.x + min.x) / 2, min.y, (max.z + min.z) / 2))
{
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->min = position + AABB_POS_OFFSET;
	this->max = min + glm::vec3(width, height, width);
	this->pos = glm::vec3((max.x + min.x) / 2, min.y, (max.z + min.z) / 2);
}
