#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "UIState.hpp"

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
	HUD(UIState& state);
	~HUD();
	void Draw();
	glm::mat4 GetProjectionMatrix() const { return proj; }

private:
	UIState& state;
	int windowW, windowH;

	// Crosshair attributes
	GLuint crosshairVAO, crosshairVBO;
	glm::mat4 proj;

	
};