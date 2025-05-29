#pragma once
#include "glm/glm.hpp"

#define AABB_POS_OFFSET glm::vec3(-0.5f, -2.0f, -0.5f)

struct AABB
{
public:
	glm::vec3 min; // world
	glm::vec3 max;
	float height;
	float width;

	// Square collision box
	AABB(const glm::vec3& position, float size);

	// Rectangular collision box
	AABB(const glm::vec3& position, float width, float height);
	
	glm::vec3 GetMin() const { return min; }
	glm::vec3 GetMax() const { return max; }
	void UpdatePosition(const glm::vec3& position);
	float GetHeight() const { return height; }
	float GetWidth() const { return width; }
};