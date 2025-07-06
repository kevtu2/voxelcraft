#pragma once
#include "UIElement.hpp"
#include "UIState.hpp"

class OptionsMenu : public UIElement
{
public:
	OptionsMenu(UIState& state, GameState& gameState);
	void Draw() override;

private:
	GameState& gameState;
};

