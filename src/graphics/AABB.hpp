#pragma once
#include "glm/glm.hpp"

#define AABB_POS_OFFSET glm::vec3(-0.5f, -2.0f, -0.5f)

struct AABB
{
public:
	glm::vec3 min; // world
	glm::vec3 max;
	unsigned int height;
	unsigned int width;

	// Square collision box
	AABB(const glm::vec3& position, unsigned int size);

	// Rectangular collision box
	AABB(const glm::vec3& position, unsigned int width, unsigned int height);
	
	glm::vec3 GetMin() const { return min; }
	glm::vec3 GetMax() const { return max; }
	void UpdatePosition(const glm::vec3& position);
	unsigned int GetHeight() const { return height; }
	unsigned int GetWidth() const { return width; }
};