#pragma once
#include "ISceneHost.hpp"
#include <memory>
#define privateSlots private

namespace RetroFuturaGUI { class Window; class Video; }

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

        /// @brief Shows the video's spectrum in the line diagram and its volume in the progress bar. The video belongs to another
        ///        window's scene, so it is handed over once both exist, and it has to outlive this scene.
        void SetVideo(RetroFuturaGUI::Video* video);

        /// @brief Lets go of the video: the line diagram drops the spectrum and the progress bar drops to zero. Call it before the video is destroyed.
        void ClearVideo();

    privateSlots:
        void on_testTextBox_textChange();
        void on_testTextBox_enterPressed();
        void on_testTextBox_enterReleased();
        void on_testTextBox_copy();
        void on_testTextBox_paste();
        void on_testTableTextChange();
        void on_testSlider_valueChanged();
        void on_scene_update();
        void on_openPopupButton_click();

    private:
        std::unique_ptr<MainScene_p> _members;
        void setup(RetroFuturaGUI::Window* parentWindow);
        void testAudioMetadata();
    };
}
