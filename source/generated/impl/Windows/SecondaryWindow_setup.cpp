#include "SecondaryWindow.hpp"
#include "SecondaryWindow_p.hpp"
#include "ScrollViewScene.hpp"
#include "CustomMenuBarScene.hpp"
#include "IncludeHelper.hpp"
#include <memory>

TestProject::SecondaryWindow::SecondaryWindow(std::string_view windowTitle, const i32 width, const i32 height)
{
    setup(windowTitle, width, height);
}

TestProject::SecondaryWindow::~SecondaryWindow()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    //The members go after this body: the scenes first, whose widgets delete their GL objects in whichever context is
    //current, and then the window. A VAO deleted in another window's context would hit that window's object instead.
    glfwMakeContextCurrent(_members->_window->GetGlfwWindow());
}

void TestProject::SecondaryWindow::Draw()
{
    if(!_members)
        return;

    if(!_members->_window)
        return;

    _members->_window->Draw();
}

bool TestProject::SecondaryWindow::WindowShouldClose() const
{
    if(!_members)
        return false;

    if(!_members->_window)
        return false;

    return _members->_window->WindowShouldClose();
}

RetroFuturaGUI::Window* TestProject::SecondaryWindow::GetWindow() const
{
    if(!_members)
        return nullptr;

    return _members->_window.get();
}

RetroFuturaGUI::Video* TestProject::SecondaryWindow::GetVideo() const
{
    if(!_members)
        return nullptr;

    if(!_members->_scrollViewScene)
        return nullptr;

    return _members->_scrollViewScene->GetVideo();
}

void TestProject::SecondaryWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    _members = std::make_unique<SecondaryWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, width, height);
    _members->_window->SetWindowTitle(windowTitle);

//Scenes draw in insertion order, so ScrollViewScene goes first and the menu bar draws over it: the ScrollView doesn't
//clip yet, and content scrolled up past its top would otherwise cover the bar. It is an overlay and reserves nothing,
//so going first doesn't take the bar's strip, and it spans whatever the bar leaves.
    std::unique_ptr<ScrollViewScene> scrollViewScene { std::make_unique<ScrollViewScene>(_members->_window.get()) };
    _members->_scrollViewScene = scrollViewScene.get();
    _members->_scenes.push_back(std::move(scrollViewScene));
    //Its own scene name, because the loader's keys span every window and the main window's bar already has "CustomMenuBarScene"
    _members->_scenes.push_back(std::make_unique<CustomMenuBarScene>(_members->_window.get(), "SecondaryCustomMenuBarScene", "test 2"));

    //No release hook, unlike MainWindow: MainScene points into ScrollViewScene's video, so the hosts stay alive until the
    //whole window closes, and MainWindow clears that link before it does.
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
