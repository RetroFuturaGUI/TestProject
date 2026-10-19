#pragma once
#include "Scene.hpp"
#include "WindowTab.hpp"
#include <memory>

namespace TestProject
{
    class TabScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };

        //Non-owning: the scene owns its root container and keeps it alive for as long as _scene lives.
        RetroFuturaGUI::WindowTab* _windowTab { nullptr };

        //Non-owning: the window this scene is in, whose corners the WindowTab follows.
        RetroFuturaGUI::Window* _window { nullptr };
    };
}
