#pragma once
#include "UIElement.hpp"
#include <string>


class TitleScreen : public UIElement
{
public:
	TitleScreen(UIState& uiState, GameState& gameState);
	void Draw() override;

private:
	float timeElapsed = 0.0f;
	std::string titleCard = "Welcome to Voxelcraft";
	ImVec2 buttonSize;
};

