#pragma once
#include "IncludeHelper.hpp"
#include <memory>
#include <string_view>

namespace RetroFuturaGUI { class Window; class Video; }

namespace TestProject
{
    class SecondaryWindow_p;

    class SecondaryWindow
    {
    public:
        /// @brief Creates the native window and builds its scenes via setup(). Leaves the new window's GL context current.
        SecondaryWindow(std::string_view windowTitle, const i32 width, const i32 height);
        SecondaryWindow() = delete;
        SecondaryWindow(const SecondaryWindow&) = delete;
        SecondaryWindow(SecondaryWindow&&) = delete;
        auto operator =(const SecondaryWindow&) = delete;
        auto operator =(SecondaryWindow&&) = delete;
        //Out of line: SecondaryWindow_p is incomplete here. Makes this window's GL context current, so its widgets delete their GL objects there.
        ~SecondaryWindow();

        /// @brief Draws one frame. It runs no loop of its own: the main window's loop calls it after drawing the main window.
        void Draw();

        /// @brief Returns whether the window has been asked to close, by its menu bar's close button or by the system.
        bool WindowShouldClose() const;

        /// @brief The framework window, so the main window can place this one beside it.
        RetroFuturaGUI::Window* GetWindow() const;

        /// @brief The video in the ScrollViewScene, for the main window's scenes that show its sound. Valid for as long as this window lives.
        RetroFuturaGUI::Video* GetVideo() const;

    private:
        std::unique_ptr<SecondaryWindow_p> _members;
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}
