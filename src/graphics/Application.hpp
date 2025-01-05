#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "blocks\Block.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

#include <stb_image.h>

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

	void ProcessInput(); // Make camera an attribute?

	void CalculateNewMousePosition();


public:
	Application(int width, int height);
	~Application();
	void Run();

};