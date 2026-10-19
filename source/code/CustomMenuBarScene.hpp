#pragma once
#include "ISceneHost.hpp"
#include <memory>
#include <string_view>
#define privateSlots private

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class CustomMenuBarScene_p;

    class CustomMenuBarScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        /// @param sceneName The loader's key for this scene, so it has to differ in every window that gets a menu bar.
        /// @param title The text drawn at the left of the bar.
        CustomMenuBarScene(RetroFuturaGUI::Window* parentWindow, std::string_view sceneName, std::string_view title);
        CustomMenuBarScene() = delete;
        CustomMenuBarScene(const CustomMenuBarScene&) = delete;
        CustomMenuBarScene(CustomMenuBarScene&&) = delete;
        auto operator =(const CustomMenuBarScene&) = delete;
        auto operator =(CustomMenuBarScene&&) = delete;
        //Out of line: CustomMenuBarScene_p is incomplete here
        ~CustomMenuBarScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    private:
        std::unique_ptr<CustomMenuBarScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow, std::string_view sceneName, std::string_view title);
    };
}
