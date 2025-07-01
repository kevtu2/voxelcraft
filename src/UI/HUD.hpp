#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

// Crosshair vertices
static constexpr float crosshairVertices[] = {
	-10.0f, 0.0f,
	 10.0f, 0.0f,
	 0.0f, -10.0f,
	 0.0f,  10.0f,
};

class HUD
{	
public:
	HUD(int width, int height);
	~HUD();
	void Draw();
	glm::mat4 GetProjectionMatrix() const { return proj; }

private:
	int windowW, windowH;

	// Crosshair attributes
	GLuint crosshairVAO, crosshairVBO;
	glm::mat4 proj;

	
};