#pragma once
#include "glm/glm.hpp"

struct AABB
{
private:
	glm::vec3 position;
	unsigned int size;
public:
	AABB(const glm::vec3& position, unsigned int size);
	
	glm::vec3 GetPosition() const { return position; }
	void UpdatePosition(const glm::vec3& position);
};