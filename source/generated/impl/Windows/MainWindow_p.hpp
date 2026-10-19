#pragma once
#include "Window.hpp"
#include "ISceneHost.hpp"
#include "MainScene.hpp"
#include "SecondaryWindow.hpp"
#include "TabWindow.hpp"
#include "NoteWindow.hpp"
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
        //Holds the secondary window and the note window in its tabs. Declared before them, so they are destroyed first, while
        //the WindowTab they sit in still exists. Null once its close button has closed it.
        std::unique_ptr<TabWindow> _tabWindow;
        //Hosts ScrollViewScene, whose video MainScene shows. Declared before _scenes so it is destroyed after them,
        //and MainScene never holds a pointer to a freed video. Null once its close button has closed it.
        std::unique_ptr<SecondaryWindow> _secondaryWindow;
        //A text box to type into while it sits in a tab. Null once its close button has closed it.
        std::unique_ptr<NoteWindow> _noteWindow;
        //Each host owns its RetroFuturaGUI::Scene and the widgets in it. Draw order follows the
        //order they were added to the window, which is what decides docking reservations.
        std::list<std::unique_ptr<RetroFuturaGUI::ISceneHost>> _scenes;
        //Non-owning: _scenes owns it. Kept as its own type to hand it the secondary window's video and take it back.
        //Null once MainScene is closed.
        MainScene* _mainScene { nullptr };
    };
}
