#include "HUD.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <stb_image.h>

HUD::HUD(int width, int height) :
	windowW(width),
	windowH(height)
{
	stbi_set_flip_vertically_on_load(true);
	crosshairData = stbi_load("../textures/crosshair.png", &cwidth, &cheight, &nrChannels, STBI_rgb_alpha);

	if (crosshairData)
	{
		glGenTextures(1, &crosshairID);
		glBindTexture(GL_TEXTURE_2D, crosshairID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cwidth, cheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, crosshairData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

HUD::~HUD()
{
	stbi_image_free(crosshairData);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void HUD::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

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
