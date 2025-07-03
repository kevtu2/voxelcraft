#pragma once

struct ImGuiIO;

class MainMenu
{
private:
	ImGuiIO& io;
public:
	MainMenu(ImGuiIO& io);

	void Draw();
	bool quitApp = false;
	bool showMainMenu = false;
};