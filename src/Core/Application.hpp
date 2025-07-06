#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/glm.hpp>

#include "world/Player.hpp"

#include "Core/ImGuiDriver.hpp"
#include "UI/UIManager.hpp"
#include "GameState.hpp"


class Application
{
private:
	GLFWwindow* window;

	// Window properties
	int width;
	int height;

	// Application runtime properties
	float deltaTime;
	float lastTime;

	// UI
	std::shared_ptr<ImGuiDriver> imgui;
	std::unique_ptr<UIManager> uiManager;

	// Game properties (states)
	GameState gameState;
	std::shared_ptr<Player> player;
	std::shared_ptr<World> world;

	void ProcessInput();

	void CalculateNewMousePosition();

public:
	Application();
	~Application();
	void Run();

	std::shared_ptr<Player> GetPlayer() const { return player; }
	float GetWorldDeltaTime() const { return deltaTime; }
	glm::vec2 GetWindowDimensions() const { return glm::vec2(width, height); }

	// Primarily used for keycallback ui state changes
	UIManager& GetUIManager() { return *uiManager; }

	void ApplyGameState();

	// Cursor positions
	float mouseX;
	float mouseY;
	float lastX = 0.0f;
	float lastY = 0.0f;
	bool firstMouseInput;
	bool overrideMouseCalculation = false;
};