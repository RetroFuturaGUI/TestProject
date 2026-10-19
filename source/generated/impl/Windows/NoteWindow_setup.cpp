#include "NoteWindow.hpp"
#include "NoteWindow_p.hpp"
#include "NoteScene.hpp"
#include "CustomMenuBarScene.hpp"
#include "IncludeHelper.hpp"
#include <memory>

TestProject::NoteWindow::NoteWindow(std::string_view windowTitle, const i32 width, const i32 height)
{
    setup(windowTitle, width, height);
}

TestProject::NoteWindow::~NoteWindow()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    //The members go after this body: the scenes first, whose widgets delete their GL objects in whichever context is
    //current, and then the window. A VAO a tab's window made for them waits until that window's context is current.
    glfwMakeContextCurrent(_members->_window->GetGlfwWindow());
}

void TestProject::NoteWindow::Draw()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    _members->_window->Draw();
}

bool TestProject::NoteWindow::WindowShouldClose() const
{
    if(!_members)
        return false;

    if(!_members->_window)
        return false;

    return _members->_window->WindowShouldClose();
}

RetroFuturaGUI::Window* TestProject::NoteWindow::GetWindow() const
{
    if(!_members)
        return nullptr;

    return _members->_window.get();
}

void TestProject::NoteWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    _members = std::make_unique<NoteWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, width, height);
    _members->_window->SetWindowTitle(windowTitle);

//The note fills whatever the menu bar leaves. Its scene is an overlay, so going first takes nothing from the bar's strip.
    _members->_scenes.push_back(std::make_unique<NoteScene>(_members->_window.get()));
    //Its own scene name, because the loader's keys span every window
    _members->_scenes.push_back(std::make_unique<CustomMenuBarScene>(_members->_window.get(), "NoteCustomMenuBarScene", "Notes"));

    for(const std::unique_ptr<RetroFuturaGUI::ISceneHost>& host : _members->_scenes)
    {
        if(!host)
            continue;

        RetroFuturaGUI::Scene* scene { host->GetScene() };

        if(!scene)
            continue;

        _members->_window->AddScene(scene);
    }
}
