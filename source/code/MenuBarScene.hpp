#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class MenuBarScene_p;

    class MenuBarScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit MenuBarScene(RetroFuturaGUI::Window* parentWindow);
        MenuBarScene() = delete;
        MenuBarScene(const MenuBarScene&) = delete;
        MenuBarScene(MenuBarScene&&) = delete;
        auto operator =(const MenuBarScene&) = delete;
        auto operator =(MenuBarScene&&) = delete;
        //Out of line: MenuBarScene_p is incomplete here
        ~MenuBarScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    private:
        std::unique_ptr<MenuBarScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
