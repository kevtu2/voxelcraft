#pragma once
#include "UIElement.hpp"
#include <vector>

class TitleScreen : public UIElement
{
public:
	TitleScreen(UIState& uiState, GameState& gameState);
	void Draw() override;

private:
	float timeElapsed = 0.0f;
	std::vector<char> titleCard;
};

