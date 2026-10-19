#pragma once
#include "Scene.hpp"
#include "MenuBar.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "TextBox.hpp"
#include "PopupScene.hpp"
#include <memory>

namespace TestProject
{
    class PopupScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };
        std::unique_ptr<RetroFuturaGUI::MenuBar> _bar { nullptr };

        //Non-owning: they sit in the bar's flex slots, which own them
        RetroFuturaGUI::Label* _barTitle { nullptr };
        RetroFuturaGUI::Button* _closeButton { nullptr };

        std::unique_ptr<RetroFuturaGUI::Label> _prompt { nullptr };
        std::unique_ptr<RetroFuturaGUI::TextBox> _nameTextBox { nullptr };
        std::unique_ptr<RetroFuturaGUI::Button>
            _okButton { nullptr },
            _cancelButton { nullptr },
            _anotherButton { nullptr };

        //Non-owning: the popup owns this scene
        PopupScene::NamePopup* _popup { nullptr };
        uSize _depth { 0 }; //how many popups lie below this one
    };
}
