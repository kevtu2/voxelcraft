#pragma once
#include "glm/glm.hpp"

#define AABB_POS_OFFSET glm::vec3(-0.5f, -2.0f, -0.5f)

// Bitmasks for collisions
#define COLLISION_POS_Z  1
#define COLLISION_NEG_Z  2
#define COLLISION_POS_X  4
#define COLLISION_NEG_X  8
#define COLLISION_POS_Y  16
#define COLLISION_NEG_Y  32

struct AABB
{
public:
	glm::vec3 min; // world
	glm::vec3 max;
	glm::vec3 pos;
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