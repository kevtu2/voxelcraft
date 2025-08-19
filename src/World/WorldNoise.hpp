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
#define C_Y2   10.0f   
#define C_Y3  10.0f   
#define C_Y4  15.0f   
#define C_Y5  90.0f   // Rapid inland rise
#define C_Y6 100.0f   // Inland plateau
#define C_Y7 120.0f   // Slight inland rise
#define C_Y8 200.0f   // Far inland max

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
	
	int GetContintentalNoiseHeight(float x, float z) const;

};