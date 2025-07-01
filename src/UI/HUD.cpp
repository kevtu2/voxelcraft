#include "HUD.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

HUD::HUD(int width, int height) :
	windowW(width),
	windowH(height)
{
	// Setup crosshair
	glGenVertexArrays(1, &crosshairVAO);
	glGenBuffers(1, &crosshairVBO);

	glBindVertexArray(crosshairVAO);
	glBindBuffer(GL_ARRAY_BUFFER, crosshairVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), crosshairVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	proj = glm::ortho(0.0f, float(windowW), 0.0f, float(windowH));
}

HUD::~HUD()
{
	stbi_image_free(crosshairData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HUD::Draw()
{
	ImGuiWindowFlags WindowFlags = 
		ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoTitleBar | 
		ImGuiWindowFlags_NoBackground | 
		ImGuiWindowFlags_NoScrollbar | 
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoSavedSettings;

	ImGui::SetNextWindowPos(ImVec2((windowW - cwidth) / 2, (windowH - cheight) / 2));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::Begin("crosshair", nullptr, WindowFlags);
	ImGui::Image((ImTextureID)(intptr_t)crosshairID, ImVec2(cwidth, cheight));
	ImGui::End();

	ImGui::PopStyleVar();
}
