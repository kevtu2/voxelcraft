#include "PerlinNoise.hpp"

float PerlinNoise::SamplePerlin(float x, float y)
{
	// Determine corner coordinates of the grid
	int x0 = (int)x;
	int y0 = (int)y;
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Interpolation weights
	float xWeight = x - (float)x0;
	float yWeight = y - (float)y0;
}
