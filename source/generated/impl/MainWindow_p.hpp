#pragma once
#include "Grid2D.hpp"
#include "Button.hpp"
#include "Window.hpp"

namespace TestProject
{
    class MainWindow_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Window> _window;


        
        std::unique_ptr<RetroFuturaGUI::Grid2d> _testGrid;
        std::unique_ptr<RetroFuturaGUI::Button> _testButton;
    };
}