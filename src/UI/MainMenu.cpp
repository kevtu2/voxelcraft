#include "MainMenu.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

MainMenu::MainMenu(UIState& state) : UIElement(state),
    windowSize(ImVec2(650, 300)),
    buttonSize(ImVec2(150, 40))
{
}

void MainMenu::Draw()
{
    ImVec2 windowCenter = ImGui::GetMainViewport()->GetCenter();

    ImGui::SetNextWindowSize(windowSize);
    ImGui::SetNextWindowPos(windowCenter, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    ImGuiIO& io = ImGui::GetIO();
    ImFont* titleFont = io.Fonts->AddFontFromFileTTF("../resources/fonts/dogica/TTF/dogica.ttf", 8.0f * contentScale);
    ImGui::PushFont(titleFont);

    if (ImGui::Begin("Main Menu", nullptr, windowFlags))
    {
        ImGuiIO& io = ImGui::GetIO();

        // Main UI
        CentreNextItem(ImGui::CalcTextSize("Voxelcraft").x);
        ImGui::Text("Voxelcraft");

        ImGui::Spacing();
        CentreNextItem(ImGui::CalcTextSize("Crafted with my tears. -Kevin").x);
        ImGui::Text("Crafted with my tears. -Kevin");

        ImGui::Dummy(ImVec2(0.0f, 10.0f));

        CentreNextItem(ImGui::CalcTextSize("Application average x.xxx ms/frame (xxx.x FPS)").x);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 30.0f));

        CentreNextItem(buttonSize.x);

        if (ImGui::Button("Resume", buttonSize))
        {
            uiState.pauseGame = false;
            uiState.showMainMenu = false;
            GLFWwindow* window = glfwGetCurrentContext();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        ImGui::Spacing();
        CentreNextItem(buttonSize.x);

        if (ImGui::Button("Options", buttonSize))
        {
            uiState.showMainMenu = false;
            uiState.showOptionsMenu = true;
        }

        ImGui::Spacing();
        CentreNextItem(buttonSize.x);

        if (ImGui::Button("Quit Game", buttonSize))
        {
            uiState.quitGame = true;
        }

        ImGui::PopFont();
        ImGui::End();
    }
}
