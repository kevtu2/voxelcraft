#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "blocks\BlockMesh.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"


class Application
{
private:
	GLFWwindow* window;
	void ProcessInput();

public:
	Application(int width, int height);
	~Application();
	void Run();
};