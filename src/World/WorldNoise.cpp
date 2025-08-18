#include "WorldNoise.hpp"
#include <iostream>

WorldNoise::WorldNoise()
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

float WorldNoise::Lerp(float x1, float x2, float y1, float y2, float x) const
{
	float slope = (y2 - y1) / (x2 - x1);
	return y1 + slope * x;
}

int WorldNoise::GetContintentalNoiseHeight(float x, float z) const
{
	float noiseVal = cNoise.GetNoise(x, z);
	std::cout << "Noise val: " << noiseVal << std::endl;
	if (noiseVal <= C_X1) return static_cast<int>(C_Y1);
	else if (noiseVal > C_X1 && noiseVal <= C_X2) return static_cast<int>(Lerp(C_X1, C_X2, C_Y1, C_Y2, noiseVal));
	else if (noiseVal > C_X2 && noiseVal <= C_X3) return static_cast<int>(Lerp(C_X2, C_X3, C_Y2, C_Y3, noiseVal));
	else if (noiseVal > C_X3 && noiseVal <= C_X4) return static_cast<int>(Lerp(C_X3, C_X4, C_Y3, C_Y4, noiseVal));
	else return static_cast<int>(C_Y4);
}
