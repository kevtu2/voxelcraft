#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	// Vertex coordinates
	float x, y, z;

	// UV Coordinates
	float u, v;

	// Cube normals
	float n_x, n_y, n_z;
	
	Vertex(const glm::vec3& positions, const glm::vec2& UV, const glm::vec3 normals)
		:
		x(positions.x),
		y(positions.y),
		z(positions.z),
		u(UV.x),
		v(UV.y),
		n_x(normals.x),
		n_y(normals.y),
		n_z(normals.z)
	{

	}
};