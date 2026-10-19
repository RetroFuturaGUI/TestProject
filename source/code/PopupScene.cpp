#include "PopupScene.hpp"
#include "PopupScene_p.hpp"
#include "Window.hpp"
#include <string>

void TestProject::PopupScene::on_okButton_click()
{
    if(!_members)
        return;

    if(!_members->_popup)
        return;

    if(!_members->_nameTextBox)
        return;

    _members->_popup->Close(true, _members->_nameTextBox->GetText());
}

void TestProject::PopupScene::on_cancelButton_click()
{
    if(!_members)
        return;

    if(!_members->_popup)
        return;

    if(!_members->_nameTextBox)
        return;

    _members->_popup->Close(false, _members->_nameTextBox->GetText());
}

void TestProject::PopupScene::on_anotherButton_click()
{
    if(!_members)
        return;

    if(!_members->_popup)
        return;

    RetroFuturaGUI::Window* window { _members->_popup->GetWindow() };

    if(!window)
        return;

    //Through this popup's window, which hands it on to the stack this popup is on
    window->PushPopup(CreatePopup(_members->_depth + 1));
}
