#pragma once
#include "ISceneHost.hpp"
#include "IncludeHelper.hpp"
#include "Popup.hpp"
#include <memory>
#include <string>
#define privateSlots private

namespace TestProject
{
    class PopupScene_p;

    /// @brief The test popup's content: a bar with its title and a close button, a prompt, a text box, OK and Cancel, and a
    ///        button that opens another popup over this one.
    class PopupScene final : public RetroFuturaGUI::ISceneHost
    {
    public:
        /// @brief Closes with whether OK was pressed, and the text box's text.
        using NamePopup = RetroFuturaGUI::Popup<bool, std::string>;

        /// @brief Builds a popup with this scene in it, with slots that print what it closes with. Hand it to Window::PushPopup.
        /// @param depth How many popups lie below it. Part of its scene's name, because the loader's keys span every window and
        ///        this popup can open another one of its own kind.
        static std::unique_ptr<NamePopup> CreatePopup(const uSize depth);

        /// @param popup The popup this scene is in, which OK and Cancel close.
        PopupScene(NamePopup* popup, const uSize depth);
        PopupScene() = delete;
        PopupScene(const PopupScene&) = delete;
        PopupScene(PopupScene&&) = delete;
        auto operator =(const PopupScene&) = delete;
        auto operator =(PopupScene&&) = delete;
        //Out of line: PopupScene_p is incomplete here
        ~PopupScene() override;

        RetroFuturaGUI::Scene* GetScene() const override;

    privateSlots:
        void on_okButton_click();
        void on_cancelButton_click();
        void on_anotherButton_click();

    private:
        std::unique_ptr<PopupScene_p> _members;
        void setup(NamePopup* popup, const uSize depth);
    };
}
