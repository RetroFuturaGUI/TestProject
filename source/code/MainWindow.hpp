#pragma once
#include "Window.hpp"
#include "MainWindow_p.hpp"
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
            _members->_window->Draw();
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