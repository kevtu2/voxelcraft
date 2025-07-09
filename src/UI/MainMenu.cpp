#include "MainMenu.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

MainMenu::MainMenu(UIState& state) : UIElement(state),
    windowSize(ImVec2(500, 250)),
    buttonSize(ImVec2(100, 20))
{
}

void MainMenu::Draw()
{
    ImVec2 windowCenter = ImGui::GetMainViewport()->GetCenter();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::Begin("Main Menu", nullptr, windowFlags))
    {
        ImGuiIO& io = ImGui::GetIO();

        // Main UI
        ImGui::Text("Voxelcraft");
        ImGui::BulletText("Crafted with my tears. -Kevin");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        float windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);

        if (ImGui::Button("Resume", buttonSize))
        {
            uiState.pauseGame = false;
            uiState.showMainMenu = false;
            GLFWwindow* window = glfwGetCurrentContext();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);

        if (ImGui::Button("Options", buttonSize))
        {
            uiState.showMainMenu = false;
            uiState.showOptionsMenu = true;
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX((windowWidth - buttonSize.x) * 0.5f);

        if (ImGui::Button("Quit Game", buttonSize))
        {
            uiState.quitGame = true;
        }
        ImGui::End();
    }
}
