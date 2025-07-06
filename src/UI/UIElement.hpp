#pragma once
#include "UIState.hpp"

class UIElement
{
public:
	UIElement(UIState& state);

protected:
	UIState& state;
	int windowW, windowH;

	virtual void Draw() = 0;
};