#pragma once
#include "UIState.hpp"
#include "Core/GameState.hpp"

class UIElement
{
public:
	UIElement(UIState& state);

protected:
	UIState& state;
	int windowW, windowH;

	virtual void Draw() = 0;

	void CentreNextItem(float itemWidth);
};