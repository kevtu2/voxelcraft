#include "TitleScreen.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>

#include <string>


TitleScreen::TitleScreen(UIState& uiState, GameState& gameState) : UIElement(uiState)
{
	std::string title = "Welcome to Voxelcraft";
}

void TitleScreen::Draw()
{
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse;
    ImVec2 windowSize = ImVec2(windowW, windowH);
    ImGui::SetNextWindowSize(windowSize);

    if (ImGui::Begin("Voxelcraft", nullptr, windowFlags))
    {
        ImGui::Text("Welcome to Voxelcraft");
    }
    ImGui::End();
}
