#pragma once
#include <math.h>

class PerlinNoise
{
public:
	float SamplePerlin(float x, float y);
	float PerlinDot(int gridX, int gridY, float x, float y);
};