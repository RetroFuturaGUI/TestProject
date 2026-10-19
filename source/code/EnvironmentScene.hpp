#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class EnvironmentScene_p;

    class EnvironmentScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit EnvironmentScene(RetroFuturaGUI::Window* parentWindow);
        EnvironmentScene() = delete;
        EnvironmentScene(const EnvironmentScene&) = delete;
        EnvironmentScene(EnvironmentScene&&) = delete;
        auto operator =(const EnvironmentScene&) = delete;
        auto operator =(EnvironmentScene&&) = delete;
        //Out of line: EnvironmentScene_p is incomplete here
        ~EnvironmentScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    privateSlots:
        void on_scene_update();

    private:
        std::unique_ptr<EnvironmentScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
