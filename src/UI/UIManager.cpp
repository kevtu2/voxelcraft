#include "UIManager.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

UIManager::UIManager(GameState& gameState) :
	window(glfwGetCurrentContext()),
	uiState(UIState()),
	titleScreen(uiState, gameState),
	mainMenu(MainMenu(uiState)),
	optionsMenu(OptionsMenu(uiState, gameState)),
	hud(HUD(uiState))
{
}

void UIManager::DrawComponents()
{
	if (uiState.showTitleScreen)
		titleScreen.Draw();
	else
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::PopFont();
		ImFont* titleFont = io.Fonts->AddFontFromFileTTF(FONT_PATH, 8.0f);
		io.Fonts->Build();
		ImGui::PushFont(titleFont);
	}

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
