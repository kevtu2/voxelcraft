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
    ImGui::Begin("Main Menu", nullptr, windowFlags);   
    ImGui::Text("Hello from main menu!");
    if (ImGui::Button("Quit App!"))
        quitApp = true;
    ImGui::End();
}
