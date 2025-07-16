#pragma once
#include <imgui.h>
#include <memory>
#include <glm/glm.hpp>

#include "TitleScreen.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
#include "HUD.hpp"
#include "Core/GameState.hpp"

#define FONT_PATH "../resources/fonts/dogica/TTF/dogica.ttf"

class GLFWwindow;

class UIManager
{
private:

	GLFWwindow* window;
	UIState uiState;

	// UI Components
	TitleScreen titleScreen;
	MainMenu mainMenu;
	OptionsMenu optionsMenu;
	HUD hud;

public:
	UIManager(GameState& gameState);

	void DrawComponents();
	void ToggleMainMenu(bool value);
	inline bool GameShouldPause() const { return uiState.pauseGame; }
	inline bool ShouldShowMainMenu() const { return uiState.showMainMenu; }
	inline bool ShouldShowTitleScreen() const { return uiState.showTitleScreen; }
	
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }
};




