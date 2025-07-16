#pragma once
#include "UIState.hpp"
#include "Core/GameState.hpp"
#include <imgui.h>

class UIElement
{
public:
	UIElement(UIState& state);

protected:
	UIState& uiState;
	ImGuiWindowFlags windowFlags;
	int contentScale;
	int windowW, windowH;
	float localFontSize = 8.0f;

	virtual void Draw() = 0;

	void CentreNextItem(float itemWidth);
	void PushFont();
};