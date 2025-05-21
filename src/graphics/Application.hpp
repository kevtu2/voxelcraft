#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VoxelShader.hpp"
#include "Renderer.hpp"
#include "Player.hpp"
#include "blocks/Texture.hpp"
#include "blocks/Chunk.hpp"
#include "graphics/LightSource.hpp"

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

	// Cursor positions
	float lastX;
	float lastY;
	bool firstMouseInput;

	void ProcessInput();

	void CalculateNewMousePosition();

public:
	Application();
	~Application();
	void Run();
	float GetWorldDeltaTime() const { return deltaTime; }
};