#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "blocks/Texture.hpp"
#include "blocks/Chunk.hpp"

class Application
{
private:
	GLFWwindow* window;
	Camera camera;

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
};