#pragma once
#include <GLFW/glfw3.h>

struct ImGuiIO;
struct ImGuiStyle;

class ImGuiDriver
{
public:
	ImGuiDriver(GLFWwindow* window);
	~ImGuiDriver();

	void StartGuiFrame();

private:
	ImGuiIO& io;
	float scale;
	ImGuiStyle& style;

	bool showMainMenu = false;
	
};

