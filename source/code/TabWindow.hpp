#pragma once
#include "IncludeHelper.hpp"
#include <memory>
#include <string_view>

namespace RetroFuturaGUI { class Window; class WindowTab; }

namespace TestProject
{
    class TabWindow_p;

    /// @brief A window whose content is a WindowTab, which other windows dock into as tabs.
    class TabWindow
    {
    public:
        /// @brief Creates the native window and builds its scenes via setup(). Leaves the new window's GL context current.
        TabWindow(std::string_view windowTitle, const i32 width, const i32 height);
        TabWindow() = delete;
        TabWindow(const TabWindow&) = delete;
        TabWindow(TabWindow&&) = delete;
        auto operator =(const TabWindow&) = delete;
        auto operator =(TabWindow&&) = delete;
        //Out of line: TabWindow_p is incomplete here. Makes this window's GL context current, so its widgets delete their GL objects there.
        ~TabWindow();

        /// @brief Draws one frame, with the window in the selected tab. It runs no loop of its own: the main window's loop calls it.
        void Draw();

        /// @brief Returns whether the window has been asked to close, by its menu bar's close button or by the system.
        bool WindowShouldClose() const;

        /// @brief The framework window, so the main window can dock this one beside it.
        RetroFuturaGUI::Window* GetWindow() const;

        /// @brief The WindowTab other windows dock into. Valid for as long as this window lives.
        RetroFuturaGUI::WindowTab* GetWindowTab() const;

    private:
        std::unique_ptr<TabWindow_p> _members;
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}
