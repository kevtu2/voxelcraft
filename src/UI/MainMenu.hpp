#pragma once
#include "UIState.hpp"

class MainMenu
{

public:
	MainMenu(UIState& state);
	void Draw();

private:
	UIState& state;
};