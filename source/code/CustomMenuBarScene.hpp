#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class CustomMenuBarScene_p;

    class CustomMenuBarScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit CustomMenuBarScene(RetroFuturaGUI::Window* parentWindow);
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
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
