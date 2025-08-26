#include "OptionsMenu.hpp"
#include "GLFW/glfw3.h"

OptionsMenu::OptionsMenu(UIState& state, GameState& gameState) :
    UIElement(state),
    gameState(gameState),
    windowSize(ImVec2(650, 300)),
    buttonSize(ImVec2(150, 40))
{
}

void OptionsMenu::Draw()
{
    ImVec2 windowCenter = ImGui::GetMainViewport()->GetCenter();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::Begin("Options", nullptr, windowFlags))
    {
        ImGui::Checkbox("Show FPS", &uiState.showFPSInHUD);
        ImGui::Checkbox("Enable flight", &gameState.enableFreeFlight);
        ImGui::SliderInt("Render Distance", &gameState.renderDistance, 5, 32);
        ImGui::SliderFloat("FOV", &gameState.FOV, 1.0f, 60.0f);
        ImGui::SliderFloat("Mouse Sensitivity", &gameState.mouseSensitivity, 0.1f, 10.0f);
        ImGui::Separator();

        ImGui::Dummy(ImVec2(0.0f, 50.0f));

        CentreNextItem(buttonSize.x);
        if (ImGui::Button("Resume", buttonSize))
        {
            uiState.showOptionsMenu = false;
            uiState.pauseGame = false;
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        CentreNextItem(buttonSize.x);
        if (ImGui::Button("Back", buttonSize))
        {
            uiState.showMainMenu = true;
            uiState.showOptionsMenu = false;
        }

        ImGui::End();
    }
}
