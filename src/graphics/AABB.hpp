#pragma once
#include "glm/glm.hpp"

struct AABB
{
private:
	glm::vec3 position; // world
	unsigned int height;
	unsigned int width;
	glm::vec3 centre;

public:
	// Square collision box
	AABB(const glm::vec3& position, unsigned int size);

	// Rectangular collision box
	AABB(const glm::vec3& position, unsigned int width, unsigned int height);
	
	glm::vec3 GetPosition() const { return position; }
	void UpdatePosition(const glm::vec3& position);
};