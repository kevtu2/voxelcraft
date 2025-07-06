#include "UIManager.hpp"
#include <GLFW/glfw3.h>

UIManager::UIManager() :
	window(glfwGetCurrentContext()),
	state(UIState()),
	mainMenu(MainMenu(state)),
	hud(HUD(state))
{
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
}

void UIManager::DrawMainMenu()
{
	if (mainMenu.showMainMenu)
		mainMenu.Draw();
	if (mainMenu.quitApp)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void UIManager::DrawHUD()
{
	if (!mainMenu.showMainMenu)
		hud.Draw();
}
