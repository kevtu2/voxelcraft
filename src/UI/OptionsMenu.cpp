#include "OptionsMenu.hpp"

#include "imgui.h"

OptionsMenu::OptionsMenu(UIState& state) : UIElement(state)
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
    }
}
