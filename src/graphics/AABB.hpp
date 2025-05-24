#pragma once
#include "glm/glm.hpp"

#define AABB_POS_OFFSET glm::vec3(-0.5f, -2.0f, -0.5f)

struct AABB
{
private:
	glm::vec3 position; // world
	unsigned int height;
	unsigned int width;

public:
	// Square collision box
	AABB(const glm::vec3& position, unsigned int size);

	// Rectangular collision box
	AABB(const glm::vec3& position, unsigned int width, unsigned int height);
	
	glm::vec3 GetPosition() const { return position; }
	void UpdatePosition(const glm::vec3& position);
	unsigned int GetHeight() const { return height; }
	unsigned int GetWidth() const { return width; }
};