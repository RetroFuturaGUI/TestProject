#pragma once
#include "Window.hpp"
#include "ISceneHost.hpp"
#include <list>
#include <memory>
#include <string>

namespace TestProject
{
    class MainWindow_p
    {
    public:
        std::string _name { "MainWindow" };
        std::unique_ptr<RetroFuturaGUI::Window> _window;
        //Each host owns its RetroFuturaGUI::Scene and the widgets in it. Draw order follows the
        //order they were added to the window, which is what decides docking reservations.
        std::list<std::unique_ptr<RetroFuturaGUI::ISceneHost>> _scenes;
    };
}
