#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	float xPos, yPos, zPos;
	float xUV, yUV;
	
	Vertex(const glm::vec3& positions, const glm::vec2& UV)
		:
		xPos(positions.x),
		yPos(positions.y),
		zPos(positions.z),
		xUV(UV.x),
		yUV(UV.y)
	{

	}
};