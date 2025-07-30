#include "TitleScreen.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>



TitleScreen::TitleScreen(UIState& uiState, GameState& gameState) : UIElement(uiState),
    buttonSize(ImVec2(800, 100))
{
    windowFlags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;
}

void TitleScreen::Draw()
{
    ImVec2 windowSize = ImVec2(uiState.monitorWidth, uiState.monitorHeight);
    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

    if (ImGui::Begin(" ", nullptr, windowFlags))
    {
        ImGui::Dummy(ImVec2(0.0f, windowSize.y * 0.35));
        CentreNextItem(ImGui::CalcTextSize(titleCard.c_str()).x);
        ImGui::Text("Welcome to Voxelcraft");

        ImGui::Dummy(ImVec2(0.0f, 50.0f));
        CentreNextItem(buttonSize.x);
        if (ImGui::Button("Play Game", buttonSize))
        {
            uiState.showTitleScreen = false;
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        ImGui::Dummy(ImVec2(0.0f, 50.0f));
        CentreNextItem(buttonSize.x);
        if (ImGui::Button("Quit to Desktop", buttonSize))
            glfwSetWindowShouldClose(glfwGetCurrentContext(), true);

        ImGui::End();
    }
}
