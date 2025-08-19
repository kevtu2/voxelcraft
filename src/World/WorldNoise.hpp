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
// Continentalness (x-axis)
#define C_X1 -1.0f    // Deep ocean floor
#define C_X2 -0.8f    // Ocean plateau
#define C_X3 -0.6f    // Coastline low shelf
#define C_X4 -0.55f   // Start of coast rise
#define C_X5 -0.1f    // Rapid rise to inland
#define C_X6  0.1f    // Inland shelf
#define C_X7  0.5f    // Inland rise
#define C_X8  1.0f    // Far inland

// Terrain height (y-axis)
#define C_Y1   0.0f   
#define C_Y2  10.0f   
#define C_Y3  10.0f   
#define C_Y4  90.0f   
#define C_Y5  90.0f   
#define C_Y6 200.0f   
#define C_Y7 230.0f   
#define C_Y8 320.0f  

/* Erosion noise spline points */
// Erosion (x-axis)
#define E_X1  -1.0f
#define E_X2  -0.8f
#define E_X3  -0.6f
#define E_X4  -0.4f
#define E_X5  -0.2f
#define E_X6   0.0f
#define E_X7   0.3f
#define E_X8   0.6f
#define E_X9   0.8f
#define E_X10  1.0f

// Terrain Height (y-axis)
#define E_Y1  300.0f
#define E_Y2  200.0f
#define E_Y3  150.0f
#define E_Y4  120.0f
#define E_Y5  100.0f
#define E_Y6  80.0f
#define E_Y7  60.0f
#define E_Y8  50.0f
#define E_Y9  55.0f
#define E_Y10 60.0f

/* Peaks and Valleys noise spline points */
// Peaks & Valleys (x-axis)
#define PV_X1 -1.0f
#define PV_X2 -0.6f
#define PV_X3 -0.3f
#define PV_X4  0.0f
#define PV_X5  0.5f
#define PV_X6  1.0f

// Terrain Height (y-axis)
#define PV_Y1  10.0f   
#define PV_Y2  25.0f  
#define PV_Y3  35.0f  
#define PV_Y4  40.0f  
#define PV_Y5  90.0f   
#define PV_Y6 100.0f

#define RUGGEDNESS_FACTOR 60

static constexpr float continentalXPoints[8] = { C_X1, C_X2, C_X3, C_X4, C_X5, C_X6, C_X7, C_X8 };
static constexpr float continentalYPoints[8] = { C_Y1, C_Y2, C_Y3, C_Y4, C_Y5, C_Y6, C_Y7, C_Y8 };
static constexpr float erosionXPoints[10] = { E_X1, E_X2, E_X3, E_X4, E_X5, E_X6, E_X7, E_X8, E_X9, E_X10 };
static constexpr float erosionYPoints[10] = { E_Y1, E_Y2, E_Y3, E_Y4, E_Y5, E_Y6, E_Y7, E_Y8, E_Y9, E_Y10 };
static constexpr float peakValleyXPoints[6] = { PV_X1, PV_X2, PV_X3, PV_X4, PV_X5, PV_X6 };
static constexpr float peakValleyYPoints[6] = { PV_Y1, PV_Y2, PV_Y3, PV_Y4, PV_Y5, PV_Y6 };

struct WorldNoise
{
private:
	FastNoiseLite cNoise; // Continental noise
	FastNoiseLite eNoise; // Erosion noise
	FastNoiseLite pvNoise; // Peak & valley noise

	float Lerp(float x1, float x2, float y1, float y2, float x) const;

public:
	WorldNoise();

	~WorldNoise() = default;
	
	int GetWorldNoiseHeight(float x, float z) const;
	inline float GetContinentalVal(float x, float z) const { return cNoise.GetNoise(x, z); }
	inline float GetErosionVal(float x, float z) const { return eNoise.GetNoise(x, z); }
	inline float GetPeakValleyVal(float x, float z) const { return pvNoise.GetNoise(x, z); }

};