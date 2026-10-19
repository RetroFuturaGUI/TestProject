#pragma once
#include "Window.hpp"
#include "ISceneHost.hpp"
#include "ScrollViewScene.hpp"
#include <list>
#include <memory>
#include <string>

namespace TestProject
{
    class SecondaryWindow_p
    {
    public:
        std::string _name { "SecondaryWindow" };
        std::unique_ptr<RetroFuturaGUI::Window> _window;
        //Each host owns its RetroFuturaGUI::Scene and the widgets in it. Draw order follows the
        //order they were added to the window.
        std::list<std::unique_ptr<RetroFuturaGUI::ISceneHost>> _scenes;
        //Non-owning: _scenes owns it. Kept as its own type so GetVideo can reach the video.
        ScrollViewScene* _scrollViewScene { nullptr };
    };
}
