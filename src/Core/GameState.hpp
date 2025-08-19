#pragma once

// Default game states
// This can be changed at runtime based on user input
struct GameState
{
	// Rendering
	int renderDistance = 12;
	float FOV = 45.0f;
	bool quitGame = false;

	// Gameplay
	float mouseSensitivity = 2.5f;
	float playerX = 0.0f;
	float playerY = 0.0f;
	float playerZ = 0.0f;

	// Utils
	float deltaTime = 0.0f;

	// Terrain Generation
	float continentalVal = 0.0f;
	float erosionVal = 0.0f;
	float pvVal = 0.0f;

};