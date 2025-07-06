#include "OptionsMenu.hpp"

#include "imgui.h"

OptionsMenu::OptionsMenu(UIState& state, GameState& gameState) :
    UIElement(state),
    gameState(gameState)
{
}

void OptionsMenu::Draw()
{
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse;

    ImVec2 windowSize = ImVec2(500, 250);
    ImVec2 buttonSize = ImVec2(100, 20);
    ImVec2 windowCenter = ImGui::GetMainViewport()->GetCenter();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::Begin("Options", nullptr, windowFlags))
    {
        ImGui::Checkbox("Show FPS", &state.showFPSInHUD);
        ImGui::SliderInt("Render Distance", &gameState.renderDistance, 5, 32);
        ImGui::SliderFloat("FOV", &gameState.FOV, 1.0f, 60.0f);
        ImGui::SliderFloat("Mouse Sensitivity", &gameState.mouseSensitivity, 0.1f, 10.0f);
    }
}
