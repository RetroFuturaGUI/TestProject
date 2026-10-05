#pragma once
#include "Scene.hpp"
#include "MenuBar.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "ComboBox.hpp"
#include "ColorPreview.hpp"
#include <memory>

namespace TestProject
{
    class CustomMenuBarScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };
        std::unique_ptr<RetroFuturaGUI::MenuBar> _menuBar { nullptr };

        /* Non-owning. Each of these sits in a flex slot, and MenuBar::AddWidget takes ownership of
           whatever it is handed, so the scene keeps plain pointers to reach them again. */
        RetroFuturaGUI::Label* _menuBarLabel { nullptr };
        RetroFuturaGUI::ColorPreview* _colorPreview { nullptr };
        RetroFuturaGUI::Button* _buttonMinimize { nullptr };
        RetroFuturaGUI::Button* _buttonMaximize { nullptr };
        RetroFuturaGUI::Button* _buttonClose { nullptr };
    };
}
