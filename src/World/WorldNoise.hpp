#pragma once
#include <FastNoiseLite.hpp>

/*
* This terrain generation system relies on the FastNoiseLite library.
* The implementation of the system is based on Henrik Kniberg's "Minecraft terrain generation in a nutshell" video.
* https://www.youtube.com/watch?v=CSa5O6knuwI&t=524s
* 
* This leverages pre-defined spline points to dictate how terrain is generated.
*/

/* Continental noise spline points */
// Contintenalness (x-axis)
#define C_X1 -1.0f
#define C_X2 0.3f
#define C_X3 0.4f
#define C_X4 1.0f

// Terrain height (y-axis)
#define C_Y1 50.0f
#define C_Y2 100.0f
#define C_Y3 150.0f
#define C_Y4 150.0f

struct WorldNoise
{
private:
	FastNoiseLite cNoise; // Continental noise
	FastNoiseLite eNoise; // Erosion noise
	FastNoiseLite pvNoise; // Peak & valley noise

	float Lerp(float x1, float x2, float y1, float y2, float x) const;

public:
	WorldNoise()
	{
		cNoise.SetSeed(rand());
		cNoise.SetFrequency(0.01f);
		cNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		eNoise.SetSeed(rand());
		eNoise.SetFrequency(0.01f);
		eNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		pvNoise.SetSeed(rand());
		pvNoise.SetFrequency(0.01f);
		pvNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	}

	~WorldNoise() = default;
	
	int GetContintentalNoiseHeight(float x, float z) const;

};