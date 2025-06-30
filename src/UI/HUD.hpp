#pragma once
#include <glad/glad.h>

class HUD
{	
public:
	HUD(int width, int height);
	~HUD();
	void Draw();

private:
	int windowW, windowH;

	int cwidth, cheight, nrChannels;
	unsigned char* crosshairData;
	GLuint crosshairID;
};