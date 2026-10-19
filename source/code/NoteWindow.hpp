#pragma once
#include "IncludeHelper.hpp"
#include <memory>
#include <string_view>

namespace RetroFuturaGUI { class Window; }

namespace TestProject
{
    class NoteWindow_p;

    /// @brief A small window with a text box, to type into while it sits in a tab.
    class NoteWindow
    {
    public:
        /// @brief Creates the native window and builds its scenes via setup(). Leaves the new window's GL context current.
        NoteWindow(std::string_view windowTitle, const i32 width, const i32 height);
        NoteWindow() = delete;
        NoteWindow(const NoteWindow&) = delete;
        NoteWindow(NoteWindow&&) = delete;
        auto operator =(const NoteWindow&) = delete;
        auto operator =(NoteWindow&&) = delete;
        //Out of line: NoteWindow_p is incomplete here. Makes this window's GL context current, so its widgets delete their GL objects there.
        ~NoteWindow();

        /// @brief Draws one frame, unless it sits in a tab, where the tab's window draws it. The main window's loop calls it.
        void Draw();

        /// @brief Returns whether the window has been asked to close, by its menu bar's or its tab's close button, or by the system.
        bool WindowShouldClose() const;

        /// @brief The framework window, so the main window can dock it into a tab.
        RetroFuturaGUI::Window* GetWindow() const;

    private:
        std::unique_ptr<NoteWindow_p> _members;
        void setup(std::string_view windowTitle, const i32 width, const i32 height);
    };
}
