#include "UIElement.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <iostream>
UIElement::UIElement(UIState& state) :
	uiState(state)
{
	windowFlags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse;
}

void UIElement::CentreNextItem(float itemWidth)
{
	float avail = ImGui::GetWindowWidth();
	ImGui::SetCursorPosX((avail - itemWidth) * 0.5f);
}

