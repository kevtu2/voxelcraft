#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "../blocks/BlockGeneration.hpp"

#define AABB_POS_OFFSET glm::vec3(-0.4753f, -2.0f, 0.4753f)

// Bitmasks for collisions
#define COLLISION_POS_Z  1
#define COLLISION_NEG_Z  2
#define COLLISION_POS_X  4
#define COLLISION_NEG_X  8
#define COLLISION_POS_Y  16
#define COLLISION_NEG_Y  32


// Each vertex: { x, y, z }
static constexpr float vertices[] = {
	// Bottom face
	-0.5f, -1.0f, -0.5f, // 0
	 0.5f, -1.0f, -0.5f, // 1
	 0.5f, -1.0f,  0.5f, // 2
	-0.5f, -1.0f,  0.5f, // 3

	// Top face
	-0.5f,  1.0f, -0.5f, // 4
	 0.5f,  1.0f, -0.5f, // 5
	 0.5f,  1.0f,  0.5f, // 6
	-0.5f,  1.0f,  0.5f  // 7
};

static constexpr float indices[] = {
	// Bottom face
   0, 1, 2,
   2, 3, 0,

   // Top face
   4, 5, 6,
   6, 7, 4,

   // Front face
   3, 2, 6,
   6, 7, 3,

   // Back face
   0, 1, 5,
   5, 4, 0,

   // Left face
   0, 3, 7,
   7, 4, 0,

   // Right face
   1, 2, 6,
   6, 5, 1
};

struct AABB
{
public:
	glm::vec3 min; // world
	glm::vec3 max;
	glm::vec3 pos;
	float height;
	float width;

	unsigned int VBO_ID;
	unsigned int VAO_ID;
	unsigned int EBO_ID;
	void GenerateAABBMesh();
	void BufferAABBData();
	void DrawArrays();

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