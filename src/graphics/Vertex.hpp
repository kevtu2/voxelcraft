#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	float x, y, z;
	float u, v;
	
	Vertex(const glm::vec3& positions, const glm::vec2& UV)
		:
		x(positions.x),
		y(positions.y),
		z(positions.z),
		u(UV.x),
		v(UV.y)
	{

	}
};