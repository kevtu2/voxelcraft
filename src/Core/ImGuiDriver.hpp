#pragma once
#include <GLFW/glfw3.h>


class ImGuiDriver
{
public:
	ImGuiDriver(GLFWwindow* window);
	~ImGuiDriver();

	void StartGuiFrame();

private:
	float scale;
};

