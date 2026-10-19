#include "EnvironmentScene.hpp"
#include "EnvironmentScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include <memory>

TestProject::EnvironmentScene::EnvironmentScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<EnvironmentScene_p>();
    setup(parentWindow);
}

TestProject::EnvironmentScene::~EnvironmentScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::EnvironmentScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::EnvironmentScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection* projection { parentWindow->GetProjection() };

    if(!projection)
        return;

    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//A backdrop scene with an Environment as its root instead of a Lasagna, so its model sits in a 3D room that keeps
//its proportions whatever the window's shape. It is an overlay, so it spans whatever the menu bar leaves, and it is
//drawn behind the other scenes because the window adds it first.
    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("EnvironmentScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_environment = _members->_scene->SetRootContainer<RetroFuturaGUI::Environment>(projection);

    if(!_members->_environment)
        return;

//Aero Lagoon
    //The lagoon is modelled within -1..1, so the default placement - centered, size 1, unrotated - fills the room exactly.
    _members->_aeroLagoon = std::make_unique<RetroFuturaGUI::Model>("AeroLagoon", projection, _members->_environment, RetroFuturaGUI::WidgetTypeID::Environment, window);
    _members->_aeroLagoon->LoadModel("Resources/aero_lagoon/aero_lagoon.obj");
    _members->_environment->AttachWidget(&*_members->_aeroLagoon);

    _members->_scene->Connect_OnUpdate([this]() { on_scene_update(); }, false);
}
