#pragma once

struct UIState
{
	// UI Properties
	int monitorWidth;
	int monitorHeight;

	// UI States
	bool quitGame = false;
	bool pauseGame = false;
	bool showMainMenu = false;
	bool showOptionsMenu = false;
	bool showFPSInHUD = false;
	bool showTitleScreen = true;
	bool createNewWorld = false;
};