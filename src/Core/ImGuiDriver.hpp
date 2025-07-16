#pragma once
#include <GLFW/glfw3.h>

class ImGuiDriver
{
public:
	ImGuiDriver(GLFWwindow* window);
	~ImGuiDriver();

	void StartGuiFrame();
	void Render();

	float GetMainScale() const { return scale; }

private:
	float scale;
};

