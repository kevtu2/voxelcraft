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
#define SMALL_FONT_SIZE 8.0f
#define LARGE_FONT_SIZE 24.0f

class GLFWwindow;

class UIManager
{
private:

	GLFWwindow* window;

	// UI Components
	TitleScreen titleScreen;
	MainMenu mainMenu;
	OptionsMenu optionsMenu;
	HUD hud;

	// Fonts
	ImFont* menuFont = nullptr;
	ImFont* titleFont = nullptr;

public:
	UIManager(GameState& gameState);

	UIState uiState;

	void DrawComponents();
	void ToggleMainMenu(bool value);
	inline bool GameShouldPause() const { return uiState.pauseGame; }
	inline bool ShouldShowMainMenu() const { return uiState.showMainMenu; }
	inline bool ShouldShowTitleScreen() const { return uiState.showTitleScreen; }
	
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }
};




