#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

// Crosshair vertices
float crosshairVertices[] = {
	-5.0f, 0.0f,
	 5.0f, 0.0f,
	 0.0f, -5.0f,
	 0.0f,  5.0f,
};

class HUD
{	
public:
	HUD(int width, int height);
	~HUD();
	void Draw();

private:
	int windowW, windowH;

	// Crosshair attributes
	GLuint crosshairVAO, crosshairVBO;
	glm::mat4 proj;
};