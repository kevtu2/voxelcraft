#include "UIElement.hpp"

#include <GLFW/glfw3.h>


UIElement::UIElement(UIState& state) :
	uiState(state)
{
	windowFlags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowW, &windowH);
}

void UIElement::CentreNextItem(float itemWidth)
{
	float avail = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX((avail - itemWidth) * 0.5f);
}
