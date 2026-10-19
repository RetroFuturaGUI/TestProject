#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; class WindowTab; }

namespace TestProject
{
    class TabScene_p;

    /// @brief A scene whose root container is a WindowTab, so the windows docked into it fill the window below its bar.
    class TabScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit TabScene(RetroFuturaGUI::Window* parentWindow);
        TabScene() = delete;
        TabScene(const TabScene&) = delete;
        TabScene(TabScene&&) = delete;
        auto operator =(const TabScene&) = delete;
        auto operator =(TabScene&&) = delete;
        //Out of line: TabScene_p is incomplete here
        ~TabScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

        /// @brief The WindowTab, so the window holding this scene can dock windows into it. Valid for as long as this scene lives.
        RetroFuturaGUI::WindowTab* GetWindowTab() const;

    privateSlots:
        void on_windowTab_selectionChanged(RetroFuturaGUI::Window* window);
        void on_scene_update();

    private:
        std::unique_ptr<TabScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
