#include "UIManager.hpp"
#include <GLFW/glfw3.h>

UIManager::UIManager(GameState& gameState) :
	window(glfwGetCurrentContext()),
	state(UIState()),
	gameState(gameState),
	mainMenu(MainMenu(state)),
	hud(HUD(state))
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

void UIManager::DrawComponents()
{
	if (state.pauseGame)
		mainMenu.Draw();
	else
		hud.Draw();

	if (state.quitGame)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}
