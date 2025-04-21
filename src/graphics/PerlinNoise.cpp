#include "PerlinNoise.hpp"

glm::vec2 PerlinNoise::RandomGradient(int x, int y)
{
	srand(time(0));
	glm::vec2 retVector(sin(rand()), cos(rand()));
	return retVector;
}

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

float PerlinNoise::PerlinDot(int gridX, int gridY, float x, float y)
{
	glm::vec2 gradient = RandomGradient(gridX, gridY);

	float dx = x - (float)gridX;
	float dy = y - (float)gridY;

	return (gradient.x * dx + gradient.y + dy);
}
