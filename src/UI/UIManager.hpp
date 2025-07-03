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
	~UIManager() = default;

	// UI Elements
	GLFWwindow* window;
	MainMenu mainMenu;
	HUD hud;

	int windowWidth, windowHeight;

public:
	static UIManager& GetManagerInstance();

	UIManager(const UIManager& other) = delete;
	void operator=(const UIManager&) = delete;

	void DrawMainMenu();
	void SetShowMainMenu(bool value) { mainMenu.showMainMenu = value; }
	bool ShouldShowMainMenu() const { return mainMenu.showMainMenu; }
	
	void DrawHUD();
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }

	ImVec2 GetWindowDimensions() const { return ImVec2(windowWidth, windowHeight); }


};




