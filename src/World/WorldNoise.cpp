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
	float continentalVal = 0;
	for (int i = 0; i < 6; ++i)
	{
		if (noiseVal > continentalXPoints[i] && noiseVal <= continentalXPoints[i + 1])
		{
			continentalVal = Lerp(continentalXPoints[i], continentalXPoints[i + 1], continentalYPoints[i], continentalYPoints[i + 1], noiseVal);
			break;
		}
	}

	if (continentalVal > 0.6f)
		noiseVal = eNoise.GetNoise(x, z);
	else
		return continentalVal;

	float erosionVal = 0;
	for (int i = 0; i < 8; ++i)
	{
		if (noiseVal > erosionXPoints[i] && noiseVal <= erosionXPoints[i + 1])
		{
			erosionVal = Lerp(erosionXPoints[i], erosionXPoints[i + 1], erosionYPoints[i], erosionYPoints[i + 1], noiseVal);
			break;
		}
	}

	if (erosionVal > 0.45f)
		noiseVal = pvNoise.GetNoise(x, z);
	else
		return erosionVal;

	for (int i = 0; i < 4; ++i)
	{
		if (noiseVal > peakValleyXPoints[i] && noiseVal <= peakValleyXPoints[i + 1])
			return Lerp(peakValleyXPoints[i], peakValleyXPoints[i + 1], peakValleyYPoints[i], peakValleyYPoints[i + 1], noiseVal);
	}
}
