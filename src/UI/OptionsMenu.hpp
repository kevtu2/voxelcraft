#pragma once
#include "UIElement.hpp"
#include "UIState.hpp"

class OptionsMenu : public UIElement
{
public:
	OptionsMenu(UIState& state);
	void Draw() override;
};

