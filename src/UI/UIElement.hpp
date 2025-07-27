#pragma once
#include "UIState.hpp"
#include "Core/GameState.hpp"
#include <imgui.h>

class UIElement
{
public:
	UIElement(UIState& state);
	virtual void Draw() = 0;

protected:
	UIState& uiState;
	ImGuiWindowFlags windowFlags;
	int contentScale;
	int windowW, windowH;

	void CentreNextItem(float itemWidth);
	ImVec2 EmVec2(float x, float y) { float k = ImGui::GetFontSize(); return ImVec2(k * x, k * y); }

};