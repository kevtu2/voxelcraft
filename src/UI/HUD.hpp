#pragma once
#include "UIElement.hpp"

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

class HUD : public UIElement
{	
public:
	HUD(UIState& state);
	~HUD();
	void Draw() override;

	glm::mat4 GetProjectionMatrix() const { return proj; }

private:
	ImVec2 windowSize;
	// Crosshair attributes
	unsigned int crosshairVAO, crosshairVBO;
	glm::mat4 proj;

	
};