#pragma once

class HUD
{	
public:
	HUD();
	~HUD();
	void Draw();

private:
	int width, height, nrChannels;
	unsigned char* crosshairData;
};