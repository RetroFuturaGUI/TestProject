#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class MainScene_p;

    class MainScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        explicit MainScene(RetroFuturaGUI::Window* parentWindow);
        MainScene() = delete;
        MainScene(const MainScene&) = delete;
        MainScene(MainScene&&) = delete;
        auto operator =(const MainScene&) = delete;
        auto operator =(MainScene&&) = delete;
        //Out of line: MainScene_p is incomplete here
        ~MainScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    privateSlots:
        void on_testButton_clicked();
        void on_testTextBox_textChange();
        void on_testTextBox_enterPressed();
        void on_testTextBox_enterReleased();
        void on_testTextBox_copy();
        void on_testTextBox_paste();
        void on_testTableTextChange();
        void on_testSlider_valueChanged();

    private:
        std::unique_ptr<MainScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
    };
}
