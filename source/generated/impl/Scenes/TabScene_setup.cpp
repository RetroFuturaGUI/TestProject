#include "TabScene.hpp"
#include "TabScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include <memory>

TestProject::TabScene::TabScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<TabScene_p>();
    setup(parentWindow);
}

TestProject::TabScene::~TabScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::TabScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

RetroFuturaGUI::WindowTab* TestProject::TabScene::GetWindowTab() const
{
    if(!_members)
        return nullptr;

    return _members->_windowTab;
}

void TestProject::TabScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection* projection { parentWindow->GetProjection() };

    if(!projection)
        return;

    _members->_window = parentWindow;

//A scene with a WindowTab as its root instead of a Lasagna, so the windows docked into it fill whatever the window's bar
//leaves. It is an overlay and reserves nothing.
    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("TabScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_windowTab = _members->_scene->SetRootContainer<RetroFuturaGUI::WindowTab>(projection);

    if(!_members->_windowTab)
        return;

    RetroFuturaGUI::WindowTab* windowTab { _members->_windowTab };
#if defined(TARGET_PLATFORM_LINUX)
    windowTab->SetTitleFontFamily("Noto Sans", 18.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    windowTab->SetTitleFontFamily("Arial", 18.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    windowTab->SetStripHeight(36.0f);
    windowTab->Connect_OnSelectionChanged([this](RetroFuturaGUI::Window* window) { on_windowTab_selectionChanged(window); }, false);
    _members->_scene->Connect_OnUpdate([this]() { on_scene_update(); }, false);
}
