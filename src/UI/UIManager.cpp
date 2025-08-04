#include "UIManager.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

UIManager::UIManager(GameState& gameState) :
	window(glfwGetCurrentContext()),
	uiState(UIState()),
	titleScreen(uiState, gameState),
	mainMenu(MainMenu(uiState)),
	optionsMenu(OptionsMenu(uiState, gameState)),
	hud(HUD(uiState))
{
	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();
	menuFont = io.Fonts->AddFontFromFileTTF(FONT_PATH, SMALL_FONT_SIZE);
	titleFont = io.Fonts->AddFontFromFileTTF(FONT_PATH, LARGE_FONT_SIZE);

	float dpiScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
	// style.ScaleAllSizes(dpiScale);
}

void UIManager::DrawComponents()
{
	if (uiState.showTitleScreen)
	{
		ImGui::PushFont(titleFont);
		titleScreen.Draw();
		ImGui::PopFont();
	}
	else
	{
		ImGui::PushFont(menuFont);

		if (uiState.showMainMenu)
			mainMenu.Draw();
		else
			hud.Draw();

		if (uiState.showOptionsMenu)
			optionsMenu.Draw();

		ImGui::PopFont();
	}
	if (uiState.quitGame)
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
}

void UIManager::ToggleMainMenu(bool value)
{
	uiState.showMainMenu = value;
	uiState.pauseGame = value;
}
