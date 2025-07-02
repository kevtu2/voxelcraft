#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "world/Player.hpp"

#include <memory>


// UI State Management
static bool showMainMenu = false;

class Application
{
private:
	GLFWwindow* window;
	std::shared_ptr<Player> player;

	// Window properties
	int width;
	int height;

	// Application runtime properties
	float deltaTime;
	float lastTime;

	void ProcessInput();

	void CalculateNewMousePosition();

public:
	Application();
	~Application();
	void Run();
	std::shared_ptr<Player> GetPlayer() const { return player; }
	float GetWorldDeltaTime() const { return deltaTime; }

	// Cursor positions
	float mouseX;
	float mouseY;
	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouseInput;
	bool overrideMouseCalculation = false;
};