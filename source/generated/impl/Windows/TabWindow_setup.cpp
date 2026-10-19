#include "TabWindow.hpp"
#include "TabWindow_p.hpp"
#include "TabScene.hpp"
#include "CustomMenuBarScene.hpp"
#include "IncludeHelper.hpp"
#include <memory>

TestProject::TabWindow::TabWindow(std::string_view windowTitle, const i32 width, const i32 height)
{
    setup(windowTitle, width, height);
}

TestProject::TabWindow::~TabWindow()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    //The members go after this body: the scenes first, the WindowTab among them, which lets the windows in its tabs go, and
    //then the window.
    glfwMakeContextCurrent(_members->_window->GetGlfwWindow());
}

void TestProject::TabWindow::Draw()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    _members->_window->Draw();
}

bool TestProject::TabWindow::WindowShouldClose() const
{
    if(!_members)
        return false;

    if(!_members->_window)
        return false;

    return _members->_window->WindowShouldClose();
}

RetroFuturaGUI::Window* TestProject::TabWindow::GetWindow() const
{
    if(!_members)
        return nullptr;

    return _members->_window.get();
}

RetroFuturaGUI::WindowTab* TestProject::TabWindow::GetWindowTab() const
{
    if(!_members)
        return nullptr;

    if(!_members->_tabScene)
        return nullptr;

    return _members->_tabScene->GetWindowTab();
}

void TestProject::TabWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    _members = std::make_unique<TabWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, width, height);
    _members->_window->SetWindowTitle(windowTitle);

//The WindowTab fills whatever the menu bar leaves. Its scene is an overlay, so going first takes nothing from the bar's strip.
    std::unique_ptr<TabScene> tabScene { std::make_unique<TabScene>(_members->_window.get()) };
    _members->_tabScene = tabScene.get();
    _members->_scenes.push_back(std::move(tabScene));
    //Its own scene name, because the loader's keys span every window
    _members->_scenes.push_back(std::make_unique<CustomMenuBarScene>(_members->_window.get(), "TabCustomMenuBarScene", "Tabs"));

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
