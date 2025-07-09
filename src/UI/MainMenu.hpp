#pragma once
#include "UIElement.hpp"
#include "UIState.hpp"
#include <imgui.h>


class MainMenu : public UIElement
{
public:
	MainMenu(UIState& state);
	void Draw() override;

private:
	ImVec2 windowSize;
	ImVec2 buttonSize;
};