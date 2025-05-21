#pragma once
#include "glm/glm.hpp"

struct AABB
{
private:
	glm::ivec3 position;
	unsigned int size;
public:
	AABB(const glm::ivec3& position, unsigned int size);
	
	glm::ivec3 GetPosition() const { return position; }

};