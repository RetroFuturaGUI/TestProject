#pragma once
#include "Window.hpp"
#include "MainWindow_p.hpp"
#include <chrono>
#define privateSlots private

namespace TestProject
{
    class MainWindow
    {
    public:
        MainWindow(std::string_view windowTitle, const i32 width, const i32 height)
        {
            setup(windowTitle, width, height);
        }  

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

                std::chrono::duration<double> frameTime =
                std::chrono::high_resolution_clock::now() - now;

                if (frameTime.count() < targetFrameTime)
                {
                    std::this_thread::sleep_for(
                        std::chrono::duration<double>(targetFrameTime - frameTime.count()));
                }
            }
        }

        bool WindowShouldClose()
        {
            return _members->_window->WindowShouldClose();
        }


    privateSlots:


        void on_testButton_clicked()
        {
            std::println("testButton Clicked!");
        }

        void on_testTextBox_textChange()
        {
            std::println("testTextBox current Text: {}", _members->_testTextBox->GetText());
        }

        void on_testTextBox_enterPressed()
        {
            std::println("Enter Pressed");
        }

        void on_testTextBox_enterReleased()
        {
            std::println("Enter Released");
        }

        std::unique_ptr<MainWindow_p> _members;
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}