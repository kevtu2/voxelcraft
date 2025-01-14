#pragma once
#include <glm\glm.hpp>


struct Face
{
	float xPos, yPos, zPos, xUV, yUV;

	Face(glm::vec3& positions, glm::vec2& UV)
		:
		xPos(positions.x),
		yPos(positions.y),
		zPos(positions.z),
		xUV(UV.x),
		yUV(UV.y)
	{

	}
};