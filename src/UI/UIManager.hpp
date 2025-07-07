#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <imgui.h>

#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
#include "HUD.hpp"
#include "Core/GameState.hpp"


class GLFWwindow;

class UIManager
{
private:

	GLFWwindow* window;
	UIState uiState;

	// UI Components

	MainMenu mainMenu;
	OptionsMenu optionsMenu;
	HUD hud;

	int windowWidth, windowHeight;

public:
	UIManager(GameState& gameState);

	void DrawComponents();
	void ToggleMainMenu(bool value);
	bool GameShouldPause() const { return uiState.pauseGame; }
	bool ShouldShowMainMenu() const { return uiState.showMainMenu; }
	bool ShouldShowTitleScreen() const { return uiState.showTitleScreen; }
	
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }
	ImVec2 GetWindowDimensions() const { return ImVec2(windowWidth, windowHeight); }

};




