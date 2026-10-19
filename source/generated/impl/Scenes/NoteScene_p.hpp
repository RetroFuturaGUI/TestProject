#pragma once
#include "Scene.hpp"
#include "MultilineTextBox.hpp"
#include <memory>

namespace TestProject
{
    class NoteScene_p
    {
    public:
        std::unique_ptr<RetroFuturaGUI::Scene> _scene { nullptr };

        //Attached to the scene's root Lasagna, which only borrows it
        std::unique_ptr<RetroFuturaGUI::MultilineTextBox> _noteTextBox { nullptr };
    };
}
