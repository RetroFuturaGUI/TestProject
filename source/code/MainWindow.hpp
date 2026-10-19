#pragma once
#include "SceneLoader.hpp"
#include "Window.hpp"
#include "MainWindow_p.hpp"
#include <chrono>

namespace TestProject
{
    class MainWindow
    {
    public:
        /// @brief Constructs the main window and sets up its widgets via setup().
        MainWindow(std::string_view windowTitle, const i32 width, const i32 height)
        {
            setup(windowTitle, width, height);
        }

        /// @brief Runs the main loop, drawing this window and the other windows each frame and capping the frame rate to 60 FPS.
        ///        It ends when this window closes, and the other windows close with it if they are still open.
        void Draw()
        {
            if(!_members)
                return;

            if(!_members->_window)
                return;

            constexpr double targetFrameTime { 1.0 / 60.0 };
	        auto lastFrameTime = std::chrono::high_resolution_clock::now();

            while(!WindowShouldClose())
            {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = now - lastFrameTime;
                lastFrameTime = now;
                //Each window makes its own GL context current before it draws. A window in a tab draws nothing itself: the tab
                //window draws the one in the selected tab.
                _members->_window->Draw();
                drawTabWindow();
                drawSecondaryWindow();
                drawNoteWindow();

                //After the draw, never during: closing a scene from a widget callback would
                //otherwise free a widget whose interact() is still on the stack.
                RetroFuturaGUI::SceneLoader::DrainPending();

                std::chrono::duration<double> frameTime =
                std::chrono::high_resolution_clock::now() - now;

                if (frameTime.count() < targetFrameTime)
                {
                    std::this_thread::sleep_for(
                        std::chrono::duration<double>(targetFrameTime - frameTime.count()));
                }
            }
        }

        /// @brief Returns whether the main window has been requested to close.
        bool WindowShouldClose()
        {
            return _members->_window->WindowShouldClose();
        }

    private:


        std::unique_ptr<MainWindow_p> _members { nullptr };
        void setup(std::string_view windowTitle, const i32 width, const i32 height);

        /// @brief Draws the secondary window, and destroys it once it has been asked to close. Its close button only raises
        ///        the flag, so the window goes here, after its draw, when none of its widgets is still running.
        void drawSecondaryWindow()
        {
            if(!_members)
                return;

            if(!_members->_secondaryWindow)
                return;

            _members->_secondaryWindow->Draw();

            if(!_members->_secondaryWindow->WindowShouldClose())
                return;

            //The video goes with the window, so MainScene lets go of it first
            releaseVideo();
            _members->_secondaryWindow.reset();
        }

        /// @brief Draws the tab window, the window in its selected tab included, and destroys it once it has been asked to close.
        ///        The windows in its tabs then become free windows again, where its content was.
        void drawTabWindow()
        {
            if(!_members)
                return;

            if(!_members->_tabWindow)
                return;

            _members->_tabWindow->Draw();

            if(!_members->_tabWindow->WindowShouldClose())
                return;

            _members->_tabWindow.reset();
        }

        /// @brief Draws the note window, and destroys it once it has been asked to close, by its tab's close button too.
        void drawNoteWindow()
        {
            if(!_members)
                return;

            if(!_members->_noteWindow)
                return;

            _members->_noteWindow->Draw();

            if(!_members->_noteWindow->WindowShouldClose())
                return;

            _members->_noteWindow.reset();
        }

        /// @brief Makes MainScene stop reading the secondary window's video.
        void releaseVideo()
        {
            if(!_members)
                return;

            if(!_members->_mainScene)
                return;

            _members->_mainScene->ClearVideo();
        }
    };
}