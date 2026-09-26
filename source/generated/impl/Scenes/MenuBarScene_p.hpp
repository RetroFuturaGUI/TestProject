#pragma once
#include "Scene.hpp"
#include "Lasagna.hpp"
#include "Label.hpp"
#include <memory>

namespace TestProject
{
    class MenuBarScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene;
        std::unique_ptr<RetroFuturaGUI::Label> _menuBarLabel;
    };
}
