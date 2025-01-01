#pragma once

constexpr float BLOCK_VERTEX_DATA[] =
{
	0, 0, 1,
	1, 0, 1,
	0, 0, 0,
	1, 0, 0,

	0, 1, 1,
	0, 1, 0,
	1, 1, 1,
	1, 1, 0
};


constexpr unsigned int BLOCK_VERTEX_INDICES[] =
{
	0, 1, 2, 2, 3, 1, // Bottom
	1, 0, 4, 4, 6, 1, // Front
	1, 3, 6, 6, 3, 7, // Right
	7, 6, 4, 4, 7, 5, // Top
	5, 2, 3, 3, 7, 5, // Back
	5, 4, 2, 2, 0, 4  // Left
};


