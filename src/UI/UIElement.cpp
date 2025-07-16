#include "UIElement.hpp"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>

UIElement::UIElement(UIState& state) :
	uiState(state)
{
	windowFlags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoCollapse;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowW, &windowH);
	contentScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
}

void UIElement::CentreNextItem(float itemWidth)
{
	float avail = ImGui::GetContentRegionAvail().x;
	ImGui::SetCursorPosX((avail - itemWidth) * 0.5f);
}
