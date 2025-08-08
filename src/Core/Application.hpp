#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <thread>
#include <mutex>

#include "World/Player.hpp"
#include "World/World.hpp"

#include "Graphics/VoxelShader.hpp"
#include "Graphics/Texture.hpp"

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
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	// UI
	std::shared_ptr<ImGuiDriver> imgui;
	std::unique_ptr<UIManager> uiManager;

	// Shaders and textures
	std::unique_ptr<VoxelShader> shaderProgram;
	std::unique_ptr<VoxelShader> crosshairShader;
	std::shared_ptr<Texture> texture;

	// Game properties (states)
	GameState gameState;
	std::shared_ptr<Player> player; // TODO: Move to world class
	std::shared_ptr<World> world;

	// Mutexes and atomic variables
	std::mutex createNewWorld;
	std::mutex applyGameStateMutex;
	std::mutex updatePlayerLocationMutex;
	std::atomic<std::shared_ptr<World>> worldAtomic;

	void ProcessInput();
	void CalculateNewMousePosition();

public:
	Application();
	~Application();
	void Run();
	void MainLoop();

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
	bool firstMouseInput = true;
	bool overrideMouseCalculation = false;
};