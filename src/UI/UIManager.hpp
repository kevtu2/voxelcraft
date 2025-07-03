#pragma once
#include <memory>
#include <glm/glm.hpp>

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

public:

	UIManager(const UIManager& other) = delete;
	void operator=(const UIManager&) = delete;

	void DrawMainMenu();
	void SetShowMainMenu(bool value) { mainMenu.showMainMenu = value; }
	bool ShouldShowMainMenu() const { return mainMenu.showMainMenu; }

	void DrawHUD();
	glm::mat4 GetHUDProjectionMat() const { return hud.GetProjectionMatrix(); }

	static UIManager& GetManagerInstance();

};




