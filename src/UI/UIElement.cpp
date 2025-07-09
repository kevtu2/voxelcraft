#include "UIElement.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

UIElement::UIElement(UIState& state) :
	state(state)
{
	glfwGetWindowSize(glfwGetCurrentContext(), &windowW, &windowH);
}

void UIElement::CentreNextItem(float itemWidth)
{
	float avail = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX((avail - itemWidth) * 0.5f);
}
