#pragma once
#include "ISceneHost.hpp"
#include <memory>

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class NoteScene_p;

    /// @brief A scene with one multiline text box filling the window, to type into while the window sits in a tab.
    class NoteScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit NoteScene(RetroFuturaGUI::Window* parentWindow);
        NoteScene() = delete;
        NoteScene(const NoteScene&) = delete;
        NoteScene(NoteScene&&) = delete;
        auto operator =(const NoteScene&) = delete;
        auto operator =(NoteScene&&) = delete;
        //Out of line: NoteScene_p is incomplete here
        ~NoteScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    private:
        std::unique_ptr<NoteScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
