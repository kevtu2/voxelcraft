#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

class Application
{
private:
	GLFWwindow* window;

public:
	Application(int width, int height);
	~Application();
	void run();
};