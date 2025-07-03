#include "UIManager.hpp"

#include <GLFW/glfw3.h>


UIManager& UIManager::GetManagerInstance()
{
	static UIManager Manager;
	return Manager;
}

UIManager::UIManager() :
	window(glfwGetCurrentContext())
{
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
