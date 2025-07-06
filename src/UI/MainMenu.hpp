#pragma once
#include "UIElement.hpp"
#include "UIState.hpp"

class MainMenu : public UIElement
{
public:
	MainMenu(UIState& state);
	void Draw() override;
};