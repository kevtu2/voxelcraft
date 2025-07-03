#include "UIManager.hpp"

#include <GLFW/glfw3.h>

UIManager::UIManager() :
	window(glfwGetCurrentContext())
{
}

UIManager& UIManager::GetInstance()
{
	static UIManager Manager;
	return Manager;
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
	hud.Draw();
}
