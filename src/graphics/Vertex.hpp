#pragma once
#include <glm\glm.hpp>
struct Vertex
{
	float xUV, yUV;
	char xPos, yPos, zPos;

	// (n)orth, (s)outh, (w)est, (e)ast, (u)p, (d)own
	char direction;

	bool transparent; 
	
	Vertex(glm::vec3& positions, glm::vec2& UV, char direction, bool transparent)
		:
		xUV(UV.x),
		yUV(UV.y),
		xPos(positions.x),
		yPos(positions.y),
		zPos(positions.z),
		direction(direction),
		transparent(transparent)
	{

	}
};