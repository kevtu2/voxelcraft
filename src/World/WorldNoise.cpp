#include "WorldNoise.hpp"
#include <iostream>

WorldNoise::WorldNoise()
{
	cNoise.SetSeed(rand());
	cNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	cNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	cNoise.SetFractalOctaves(6);
	cNoise.SetFractalGain(0.290f);
	cNoise.SetFractalLacunarity(2.380f);
	cNoise.SetFractalWeightedStrength(-0.920f);
	cNoise.SetFrequency(0.002f);

	eNoise.SetSeed(rand());
	eNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	eNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	eNoise.SetFractalOctaves(6);
	eNoise.SetFractalGain(0.080f);
	eNoise.SetFractalLacunarity(0.930f);
	eNoise.SetFractalWeightedStrength(25.280f);
	eNoise.SetFrequency(0.005f);

	pvNoise.SetSeed(rand());
	pvNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	pvNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);
	pvNoise.SetFractalOctaves(4);
	pvNoise.SetFractalGain(0.490f);
	pvNoise.SetFractalLacunarity(0.40f);
	pvNoise.SetFractalWeightedStrength(-0.640f);
	pvNoise.SetFractalPingPongStrength(4.150f);
	pvNoise.SetFrequency(0.01f);
}

float WorldNoise::Lerp(float x1, float x2, float y1, float y2, float x) const
{
	return y1 + ((y2 - y1) / (x2 - x1)) * (x - x1);
}

int WorldNoise::GetWorldNoiseHeight(float x, float z) const
{
	float noiseVal = cNoise.GetNoise(x, z);
	if (noiseVal <= C_X1)
		return static_cast<int>(C_Y1);

	else if (noiseVal > C_X1 && noiseVal <= C_X2)
		return static_cast<int>(Lerp(C_X1, C_X2, C_Y1, C_Y2, noiseVal));

	else if (noiseVal > C_X2 && noiseVal <= C_X3)
		return static_cast<int>(Lerp(C_X2, C_X3, C_Y2, C_Y3, noiseVal));

	else if (noiseVal > C_X3 && noiseVal <= C_X4)
		return static_cast<int>(Lerp(C_X3, C_X4, C_Y3, C_Y4, noiseVal));

	else if (noiseVal > C_X4 && noiseVal <= C_X5)
		return static_cast<int>(Lerp(C_X4, C_X5, C_Y4, C_Y5, noiseVal));

	else if (noiseVal > C_X5 && noiseVal <= C_X6)
		return static_cast<int>(Lerp(C_X5, C_X6, C_Y5, C_Y6, noiseVal));

	else if (noiseVal > C_X6 && noiseVal <= C_X7)
		return static_cast<int>(Lerp(C_X6, C_X7, C_Y6, C_Y7, noiseVal));

	else if (noiseVal > C_X7 && noiseVal <= C_X8)
		return static_cast<int>(Lerp(C_X7, C_X8, C_Y7, C_Y8, noiseVal));

	return static_cast<int>(C_Y8);
}
