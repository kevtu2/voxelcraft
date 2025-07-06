#include "UIElement.hpp"

#include <GLFW/glfw3.h>

UIElement::UIElement(UIState& state) :
	state(state)
{
	glfwGetWindowSize(glfwGetCurrentContext(), &windowW, &windowH);
}
