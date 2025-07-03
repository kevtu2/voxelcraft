#include "MainMenu.hpp"

#include <imgui.h>
#include <iostream>

MainMenu::MainMenu()
{

}

void MainMenu::Draw()
{
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse;

    ImGui::SetNextWindowSize(ImVec2(500, 250));

    if (ImGui::Begin("Main Menu", nullptr, windowFlags))
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Voxelcraft");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        if (ImGui::Button("Quit App!"))
            quitApp = true;
    }

    ImGui::End();
}
