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

        /// @brief Runs the main loop, drawing the window each frame and capping the frame rate to 60 FPS.
        void Draw()
        {
            constexpr double targetFrameTime { 1.0 / 60.0 };
	        auto lastFrameTime = std::chrono::high_resolution_clock::now();

            while(!WindowShouldClose())
            {
                auto now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = now - lastFrameTime;
                lastFrameTime = now;
                _members->_window->Draw();

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
    };
}