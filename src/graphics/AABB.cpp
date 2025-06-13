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

void AABB::GenerateAABBMesh()
{
	glGenVertexArrays(1, &VAO_ID);
	glGenBuffers(1, &VBO_ID);
	glGenBuffers(1, &EBO_ID);
}

void AABB::BufferAABBData()
{
	glBindVertexArray(VAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void AABB::DrawArrays()
{
	glBindVertexArray(VAO_ID);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void AABB::UpdatePosition(const glm::vec3& position)
{
	this->min = position;
	this->max = min + glm::vec3(width, height, width);
	this->pos = glm::vec3((max.x + min.x) / 2, min.y, (max.z + min.z) / 2);
}
