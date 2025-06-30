#include "HUD.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <stb_image.h>

HUD::HUD()
{
	stbi_set_flip_vertically_on_load(true);
	crosshairData = stbi_load("../textures/crosshair.png", &width, &height, &nrChannels, STBI_rgb);

	if (crosshairData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, crosshairData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

HUD::~HUD()
{
	stbi_image_free(crosshairData);
}

void HUD::Draw()
{
	bool WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar;
	ImGui::Begin("crosshair", WindowFlags);
	ImGui::Image((ImTextureID)crosshairData, ImVec2(width, height));
	ImGui::End();
}
