#pragma once
#include "Window.hpp"
#include "MainWindow_p.hpp"

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


    private:
    //private slots


        void on_testButton_clicked()
        {
            std::println("testButton Clicked!");
        }


        std::unique_ptr<MainWindow_p> _members;
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}