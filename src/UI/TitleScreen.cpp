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
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;
    ImVec2 windowSize = ImVec2(windowW, windowH);
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

    if (ImGui::Begin(" ", nullptr, windowFlags))
    {
        ImGui::Text("Welcome to Voxelcraft");
    }
    ImGui::End();
}
