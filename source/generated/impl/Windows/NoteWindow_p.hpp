#pragma once
#include "Window.hpp"
#include "ISceneHost.hpp"
#include <list>
#include <memory>
#include <string>

namespace TestProject
{
    class NoteWindow_p
    {
    public:
        std::string _name { "NoteWindow" };
        std::unique_ptr<RetroFuturaGUI::Window> _window;
        //Each host owns its RetroFuturaGUI::Scene and the widgets in it. Draw order follows the
        //order they were added to the window.
        std::list<std::unique_ptr<RetroFuturaGUI::ISceneHost>> _scenes;
    };
}
