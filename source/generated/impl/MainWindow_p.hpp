#pragma once
#include "Lasagna.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "Window.hpp"
#include "TextBox.hpp"
#include "Image.hpp"
#include "Model.hpp"
#include <memory>

namespace TestProject
{
    class MainWindow_p
    {
    public:
        std::string _name { "MainWindow" };
        std::unique_ptr<RetroFuturaGUI::Window> _window;


        
        std::unique_ptr<RetroFuturaGUI::Lasagna> _testLasagna;
        std::unique_ptr<RetroFuturaGUI::Button> _testButton;
        std::unique_ptr<RetroFuturaGUI::Label> _testLabel;
        std::unique_ptr<RetroFuturaGUI::TextBox> _testTextBox;
        std::unique_ptr<RetroFuturaGUI::Image> _testImage;
        std::unique_ptr<RetroFuturaGUI::Model> _testModel;
    };
}