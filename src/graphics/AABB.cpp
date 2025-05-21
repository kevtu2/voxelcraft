#include "AABB.hpp"

AABB::AABB(const glm::vec3& position, unsigned int size) :
	position(position),
	size(size)
{
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->position = position;
}
