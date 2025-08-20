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
	cNoise.SetFrequency(0.0015f);

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
	float terrainHeight = BASE_HEIGHT;

	float cNoiseVal = cNoise.GetNoise(x, z);
	float continentalVal = 0;
	for (int i = 0; i < 7; ++i)
	{
		if (cNoiseVal >= continentalXPoints[i] && cNoiseVal <= continentalXPoints[i + 1])
		{
			continentalVal = Lerp(
				continentalXPoints[i], continentalXPoints[i + 1], 
				continentalYPoints[i], continentalYPoints[i + 1], 
				cNoiseVal
			);
			break;
		}
	}

	terrainHeight += continentalVal;

	float eNoiseVal = eNoise.GetNoise(x, z);
	float erosionVal = 0;
	for (int i = 0; i < 9; ++i)
	{
		if (eNoiseVal >= erosionXPoints[i] && eNoiseVal <= erosionXPoints[i + 1])
		{
			erosionVal = Lerp(
				erosionXPoints[i], erosionXPoints[i + 1], 
				erosionYPoints[i], erosionYPoints[i + 1], 
				eNoiseVal
			);
			break;
		}
	}
	terrainHeight -= erosionVal;

	float pvNoiseVal = pvNoise.GetNoise(x, z);
	float pvVal = 0;
	for (int i = 0; i < 5; ++i)
	{
		if (pvNoiseVal >= peakValleyXPoints[i] && pvNoiseVal <= peakValleyXPoints[i + 1])
		{
			pvVal = Lerp(
				peakValleyXPoints[i], peakValleyXPoints[i + 1],
				peakValleyYPoints[i], peakValleyYPoints[i + 1],
				pvNoiseVal
			);
			break;
		}
	}
	terrainHeight += pvVal;

	return static_cast<int>(terrainHeight);
}
