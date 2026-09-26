#include "MenuBarScene.hpp"
#include "MenuBarScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>

TestProject::MenuBarScene::MenuBarScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<MenuBarScene_p>();
    setup(parentWindow);
}

TestProject::MenuBarScene::~MenuBarScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(_members && _members->_scene)
        RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::MenuBarScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::MenuBarScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection& projection { *parentWindow->GetProjection() };
    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//Throwaway docked scene, to exercise the client-rect pass: it reserves a strip across the top,
//so MainScene should be fitted underneath it rather than running behind it.
    RetroFuturaGUI::AxisDefinition menuBarAxis
    {
        ._RowDefinition    = { 1.0f },
        ._ColumnDefinition = { 0.25f, 0.25f, 0.5f },
        ._LayerDefinition  = { 1.0f }
    };

    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("MenuBarScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(menuBarAxis, &projection);
    _members->_scene->SetReservedEdge(RetroFuturaGUI::DockEdge::Top, 40.0f);

    if(RetroFuturaGUI::Lasagna* _rootLasagna { _members->_scene->GetRootLasagna() })
    {
        _members->_menuBarLabel = std::make_unique<RetroFuturaGUI::Label>("TestMenuBarLabel", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
        _members->_menuBarLabel->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
        _members->_menuBarLabel->SetText("Docked MenuBar Scene", false);
        _members->_menuBarLabel->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
        _members->_menuBarLabel->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
        _members->_menuBarLabel->SetTextPadding(5.0f);
        _rootLasagna->AttachWidget(0, 0, 0, &*_members->_menuBarLabel, RetroFuturaGUI::SizingMode::FILL, 1, 2);
    }
}
