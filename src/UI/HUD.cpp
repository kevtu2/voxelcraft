#include "HUD.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

HUD::HUD(UIState& state) : UIElement(state),
	windowSize(ImVec2(200, 100))
{
	windowFlags |= ImGuiWindowFlags_NoTitleBar;

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

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	float xScale, yScale;
	glfwGetMonitorContentScale(primaryMonitor, &xScale, &yScale);
	float dpiScale = xScale;

	float windowW = mode->width / dpiScale;
	float windowH = mode->height / dpiScale;

	proj = glm::ortho(0.0f, float(windowW), 0.0f, float(windowH));
}

HUD::~HUD()
{
	glDeleteBuffers(1, &crosshairVBO);
	glDeleteVertexArrays(1, &crosshairVAO);
}

void HUD::Draw()
{
	glBindVertexArray(crosshairVAO);
	glDisable(GL_DEPTH_TEST);

	glLineWidth(1.5f);
	glDrawArrays(GL_LINES, 0, 4);
	glEnable(GL_DEPTH_TEST);

	ImGui::SetNextWindowSize(windowSize);
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	ImGui::SetNextWindowBgAlpha(0.5f);

	ImGuiIO& io = ImGui::GetIO();

	if (uiState.showFPSInHUD)
	{
		if (ImGui::Begin("Metrics", nullptr, windowFlags))
		{
			CentreNextItem(ImGui::CalcTextSize("xxx FPS").x);
			ImGui::Text("%d FPS", (int)io.Framerate);
			
			ImGui::Spacing();

			CentreNextItem(ImGui::CalcTextSize("%.3f ms/frame").x);
			ImGui::Text("%.3f ms/frame", 1000.0f / io.Framerate);
			ImGui::End();
		}
	}

	ImGui::SetNextWindowBgAlpha(1.0f);
}
