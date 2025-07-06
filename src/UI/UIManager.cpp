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
	if (uiState.pauseGame)
		mainMenu.Draw();
	else
		hud.Draw();

	if (uiState.quitGame)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}
