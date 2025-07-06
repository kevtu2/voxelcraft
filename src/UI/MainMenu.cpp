#include "MainMenu.hpp"

#include <imgui.h>
#include <iostream>
#include <GLFW/glfw3.h>

MainMenu::MainMenu(UIState& state) : UIElement(state)
{
}

void MainMenu::Draw()
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

    if (ImGui::Begin("Main Menu", nullptr, windowFlags))
    {
        ImGuiIO& io = ImGui::GetIO();

        // Main UI
        ImGui::Text("Voxelcraft");
        ImGui::BulletText("Crafted with my tears. -Kevin");
        ImGui::Separator();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        if (ImGui::Button("Resume", buttonSize))
        {
            state.pauseGame = false;
            GLFWwindow* window = glfwGetCurrentContext();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
            
        if (ImGui::Button("Quit Game", buttonSize))
            state.quitGame = true;
    }

    ImGui::End();
}
