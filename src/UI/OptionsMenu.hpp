#pragma once
#include "UIElement.hpp"
#include "UIState.hpp"
#include <imgui.h>


class OptionsMenu : public UIElement
{
public:
	OptionsMenu(UIState& state, GameState& gameState);
	void Draw() override;

private:
	GameState& gameState;
	ImVec2 windowSize;
	ImVec2 buttonSize;
};

