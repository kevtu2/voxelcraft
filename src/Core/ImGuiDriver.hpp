#pragma once
#include <GLFW/glfw3.h>

#define USER_DEFAULT_SCREEN_DPI 96

class ImGuiDriver
{
public:
	ImGuiDriver(GLFWwindow* window);
	~ImGuiDriver();

	void StartGuiFrame();
	void Render();


};

