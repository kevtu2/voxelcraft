#pragma once

// Default game states
// This can be changed at runtime based on user input
struct GameState
{
	// Rendering
	int renderDistance = 12;
	float FOV = 45.0f;

	// Gameplay
	float mouseSensitivity = 2.5f;

};