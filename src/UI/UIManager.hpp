#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <imgui.h>

#include "MainMenu.hpp"
#include "HUD.hpp"

class GLFWwindow;

class UIManager
{
private:
	UIManager();

	// UI Elements
	GLFWwindow* window;
	UIState& state;
	MainMenu mainMenu;
	HUD hud;

	int windowWidth, windowHeight;

public:
	void DrawMainMenu();
	void SetShowMainMenu(bool value) { mainMenu.showMainMenu = value; }
	bool ShouldShowMainMenu() const { return mainMenu.showMainMenu; }
	
	void DrawHUD();
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }

	ImVec2 GetWindowDimensions() const { return ImVec2(windowWidth, windowHeight); }


};




