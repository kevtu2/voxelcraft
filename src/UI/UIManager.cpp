#include "UIManager.hpp"
#include <GLFW/glfw3.h>

UIManager::UIManager(GameState& gameState) :
	window(glfwGetCurrentContext()),
	uiState(UIState()),
	mainMenu(MainMenu(uiState)),
	optionsMenu(OptionsMenu(uiState, gameState)),
	hud(HUD(uiState))
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

void UIManager::DrawComponents()
{
	if (uiState.showMainMenu)
		mainMenu.Draw();
	else
		hud.Draw();

	if (uiState.showOptionsMenu)
		optionsMenu.Draw();

	if (uiState.quitGame)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void UIManager::ToggleMainMenu(bool value)
{
	uiState.showMainMenu = value;
	uiState.pauseGame = value;
}
