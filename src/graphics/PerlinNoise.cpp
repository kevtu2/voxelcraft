#include "PerlinNoise.hpp"

glm::vec2 PerlinNoise::RandomGradient(int x, int y)
{
	srand(time(0));
	glm::vec2 retVector(sin(rand()), cos(rand()));
	return retVector;
}

float PerlinNoise::PerlinInterpolate(float x, float y, float weight)
{
	// Utilizes cubic interpolation
	return (y - x) * (3.0 - weight * 2.0) * weight * weight + x;
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

	// Calculate gradients and interpolation for top corners
	float g_TopL = PerlinDot(x0, y0, x, y);
	float g_TopR = PerlinDot(x1, y0, x, y);
	float topInterp = PerlinInterpolate(g_TopL, g_TopR, xWeight);

	// Calculate gradients and interpolation for bottom corners
	float g_BotL = PerlinDot(x0, y1, x, y);
	float g_BotR = PerlinDot(x1, y1, x, y);
	float botInterp = PerlinInterpolate(g_BotL, g_BotR, xWeight);

	float ret = PerlinInterpolate(topInterp, botInterp, yWeight);

	return ret;
}

float PerlinNoise::PerlinDot(int gridX, int gridY, float x, float y)
{
	glm::vec2 gradient = RandomGradient(gridX, gridY);

	float dx = x - (float)gridX;
	float dy = y - (float)gridY;

	return (gradient.x * dx + gradient.y + dy);
}
