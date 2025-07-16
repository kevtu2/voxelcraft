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
	int windowW, windowH;
	int contentScale;

	virtual void Draw() = 0;

	void CentreNextItem(float itemWidth);
};