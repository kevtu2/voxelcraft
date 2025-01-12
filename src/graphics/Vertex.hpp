#pragma once
#include <glm\glm.hpp>
struct Vertex
{
	float xPos, yPos, zPos, xUV, yUV;
	Vertex(glm::vec3& positions, glm::vec2& UV)
	{
		xPos = positions.x;
		yPos = positions.y;
		zPos = positions.z;
		xUV = UV.x;
		yUV = UV.y;
	}
};