#include "MainMenu.hpp"

#include <imgui.h>
#include <iostream>
#include <GLFW/glfw3.h>

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

        // Main UI
        ImGui::Text("Voxelcraft");
        ImGui::BulletText("Crafted with my tears. -Kevin");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        if (ImGui::Button("Resume"))
        {
            showMainMenu = false;
            GLFWwindow* window = glfwGetCurrentContext();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
            
        if (ImGui::Button("Quit App!"))
            quitApp = true;
    }

    ImGui::End();
}
