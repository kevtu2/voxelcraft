#pragma once
#include <math.h>
#include <glm/glm.hpp>


class PerlinNoise
{
private:
	glm::vec2 RandomGradient(int x, int y);
	float PerlinInterpolate(float x, float y, float weight);
	float PerlinDot(int gridX, int gridY, float x, float y);

public:
	float SamplePerlin(float x, float y);
};