#include "NoteScene.hpp"
#include "NoteScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include <memory>
#include <vector>

TestProject::NoteScene::NoteScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<NoteScene_p>();
    setup(parentWindow);
}

TestProject::NoteScene::~NoteScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::NoteScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::NoteScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection* projection { parentWindow->GetProjection() };

    if(!projection)
        return;

    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//The text box takes the middle cell, a small margin away from the edges of whatever the window's bar leaves - or, while the
//window sits in a tab, of the tab's content area
    const RetroFuturaGUI::AxisDefinition axisDefinition
    {
        ._RowDefinition = { 0.03f, 0.94f, 0.03f },
        ._ColumnDefinition = { 0.03f, 0.94f, 0.03f },
        ._LayerDefinition = { 1.0f }
    };

    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("NoteScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(axisDefinition, projection);
    RetroFuturaGUI::Lasagna* rootLasagna { _members->_scene->GetRootContainer<RetroFuturaGUI::Lasagna>() };

    if(!rootLasagna)
        return;

    _members->_noteTextBox = std::make_unique<RetroFuturaGUI::MultilineTextBox>("NoteTextBox", projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    RetroFuturaGUI::MultilineTextBox* noteTextBox { _members->_noteTextBox.get() };

    if(!noteTextBox)
        return;

    noteTextBox->SetBackgroundColor(glm::vec4(0.12f, 0.12f, 0.16f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    noteTextBox->SetBackgroundColor(glm::vec4(0.15f, 0.15f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    noteTextBox->SetBackgroundColor(glm::vec4(0.15f, 0.15f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    noteTextBox->SetBackgroundColor(glm::vec4(0.08f, 0.08f, 0.1f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
    noteTextBox->SetBorderColor(glm::vec4(0.35f, 0.35f, 0.45f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    noteTextBox->SetBorderColor(glm::vec4(0.45f, 0.45f, 0.6f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    noteTextBox->SetBorderColor(glm::vec4(0.55f, 0.55f, 0.75f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    noteTextBox->SetBorderWidth(1.0f);
    noteTextBox->SetCornerRadii(glm::vec4(8.0f));
#if defined(TARGET_PLATFORM_LINUX)
    noteTextBox->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    noteTextBox->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    noteTextBox->SetText("", false);
    noteTextBox->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    noteTextBox->SetTextPadding(8.0f);
    noteTextBox->SetPlaceholderText("Type here, also while this window sits in a tab...");
    noteTextBox->SetPlaceholderTextColor(glm::vec4(0.5f, 0.5f, 0.55f, 1.0f));

    std::vector<glm::vec4> caretColors { glm::vec4(0.85f, 0.85f, 0.9f, 1.0f) };
    noteTextBox->SetCaretColors(caretColors);
    noteTextBox->SetCaretBlinkTime(750.0);

    rootLasagna->AttachWidget(1, 1, 0, noteTextBox, RetroFuturaGUI::SizingMode::FILL_XY);
}
