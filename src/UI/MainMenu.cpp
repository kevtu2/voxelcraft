#include "MainMenu.hpp"

#include <imgui.h>
#include <iostream>

MainMenu::MainMenu()
{

}

void MainMenu::Draw()
{
    ImGui::Begin("Main Menu");   
    ImGui::Text("Hello from main menu!");
    if (ImGui::Button("Press Me!"))
        std::cout << "Button pressed!" << std::endl;
    ImGui::End();
}
