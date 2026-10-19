#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; class Video; }

namespace TestProject
{
    class ScrollViewScene_p;

    class ScrollViewScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit ScrollViewScene(RetroFuturaGUI::Window* parentWindow);
        ScrollViewScene() = delete;
        ScrollViewScene(const ScrollViewScene&) = delete;
        ScrollViewScene(ScrollViewScene&&) = delete;
        auto operator =(const ScrollViewScene&) = delete;
        auto operator =(ScrollViewScene&&) = delete;
        //Out of line: ScrollViewScene_p is incomplete here
        ~ScrollViewScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

        /// @brief The video in the ScrollView, for widgets in other scenes that show its sound. Valid for as long as this scene lives.
        RetroFuturaGUI::Video* GetVideo() const;

    privateSlots:
        void on_testButton_clicked();

    private:
        std::unique_ptr<ScrollViewScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
