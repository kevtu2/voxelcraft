#pragma once
#include <GLFW/glfw3.h>

struct ImGuiIO;
class UserInterface
{
public:
	UserInterface(GLFWwindow* window);
	~UserInterface();

	void StartFrame();

protected:
	ImGuiIO& io;
	float scale;
	ImGuiStyle& style;

	// To be defined and displays the contents of the window.
	virtual void Window() = 0;

};

