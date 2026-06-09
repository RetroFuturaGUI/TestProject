#pragma once
#include "Lasagna.hpp"
#include "Button.hpp"
#include "Window.hpp"
#include "TextBox.hpp"

namespace TestProject
{
    class MainWindow_p
    {
    public:
        std::string _name { "MainWindow" };
        std::unique_ptr<RetroFuturaGUI::Window> _window;


        
        std::unique_ptr<RetroFuturaGUI::Lasagna> _testLasagna;
        std::unique_ptr<RetroFuturaGUI::Button> _testButton;
        std::unique_ptr<RetroFuturaGUI::TextBox> _testTextBox;
    };
}