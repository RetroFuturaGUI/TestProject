#include "PopupScene.hpp"
#include "PopupScene_p.hpp"
#include "Window.hpp"
#include "Lasagna.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include <glm/ext/vector_float3.hpp>
#include <cstdio>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

std::unique_ptr<TestProject::PopupScene::NamePopup> TestProject::PopupScene::CreatePopup(const uSize depth)
{
    //Creating the popup leaves its window's context current, which its scene is built in
    std::unique_ptr<NamePopup> popup { std::make_unique<NamePopup>(std::format("NamePopup{}", depth), 480, 260) };
    RetroFuturaGUI::Window* window { popup->GetWindow() };

    if(!window)
        return popup;

    window->SetWindowTitle(std::format("Popup {}", depth + 1));
    window->SetCornerRadii(glm::vec4(12.0f));
    window->SetBorderWidth(1.0f);
    window->SetBorderColor(glm::vec4(0.35f, 0.35f, 0.45f, 1.0f), RetroFuturaGUI::ColorState::Enabled);

    popup->AddScene(std::make_unique<PopupScene>(popup.get(), depth));

    //What it closes with goes to whoever opened it. Here that is printed.
    popup->Connect_OnResult([depth](bool accepted, std::string name)
        {
            std::println("Popup {} closed: accepted {}, name \"{}\"", depth + 1, accepted, name);
            std::fflush(stdout);
        }, false);

    popup->Connect_OnDismiss([depth]()
        {
            std::println("Popup {} dismissed", depth + 1);
            std::fflush(stdout);
        }, false);

    return popup;
}

TestProject::PopupScene::PopupScene(NamePopup* popup, const uSize depth)
{
    _members = std::make_unique<PopupScene_p>();
    setup(popup, depth);
}

TestProject::PopupScene::~PopupScene()
{
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    //Unregister before the scene is freed, or the loader's registry and the window's draw order are left holding a pointer to it
    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::PopupScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::PopupScene::setup(NamePopup* popup, const uSize depth)
{
    if(!popup)
        return;

    RetroFuturaGUI::Window* parentWindow { popup->GetWindow() };

    if(!parentWindow)
        return;

    _members->_popup = popup;
    _members->_depth = depth;

    RetroFuturaGUI::Projection& projection { *parentWindow->GetProjection() };
    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//Bar on top, then the prompt, the text box, and a row of three buttons
    RetroFuturaGUI::AxisDefinition axisDefinition
    {
        ._RowDefinition    = { 0.16f, 0.2f, 0.26f, 0.38f },
        ._ColumnDefinition = { 0.3333f, 0.3333f, 0.3334f },
        ._LayerDefinition  = { 1.0f }
    };

    //Numbered, because the loader's keys span every window and a popup of this kind can open over another one
    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene(std::format("PopupScene{}", depth), parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(axisDefinition, &projection);
    RetroFuturaGUI::Lasagna* rootLasagna { _members->_scene->GetRootContainer<RetroFuturaGUI::Lasagna>() };

    if(!rootLasagna)
        return;

//Bar
    _members->_bar = std::make_unique<RetroFuturaGUI::MenuBar>("PopupBar", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_bar->SetDockingEdge(RetroFuturaGUI::MenuBar::DockingEdge::Top);
    _members->_bar->SetBackgroundColor(glm::vec4(0.08f, 0.08f, 0.12f, 0.9f), RetroFuturaGUI::ColorState::Enabled);
    _members->_bar->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_bar->SetBorderColor(glm::vec4(0.35f, 0.35f, 0.45f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_bar->SetBorderWidth(1.0f);
    _members->_bar->SetCornerRadii(glm::vec4(12.0f, 12.0f, 0.0f, 0.0f)); //the window's top corners, which a popup never squares
    _members->_bar->SetItemBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_bar->SetItemBackgroundColor(glm::vec4(0.25f, 0.25f, 0.35f, 0.9f), RetroFuturaGUI::ColorState::Hover);
    _members->_bar->SetItemBackgroundColor(glm::vec4(0.35f, 0.35f, 0.5f, 0.95f), RetroFuturaGUI::ColorState::Clicked);
    _members->_bar->SetItemBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.6f), RetroFuturaGUI::ColorState::Disabled);
    _members->_bar->SetItemBorderColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_bar->SetItemBorderColor(glm::vec4(0.5f, 0.5f, 0.65f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_bar->SetItemBorderColor(glm::vec4(0.6f, 0.6f, 0.8f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_bar->SetItemBorderColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_bar->SetItemBorderWidth(1.0f);

    //The title drags the popup, the spacer takes what is left, and the close button is a square of the bar's height
    std::vector<RetroFuturaGUI::MenuBar::FlexDefinition> flexDefinition
    {
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Auto,   ._Width = 0.0f, ._IsWindowDrag = true,  ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Star,   ._Width = 1.0f, ._IsWindowDrag = false, ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = false }
    };
    _members->_bar->SetFlexDefinition(flexDefinition);

    std::unique_ptr<RetroFuturaGUI::Label> barTitle
    {
        std::make_unique<RetroFuturaGUI::Label>("PopupBarTitle", &projection, &*_members->_bar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    barTitle->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    barTitle->SetText(std::format("Popup {}", depth + 1), false);
    barTitle->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    barTitle->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    barTitle->SetTextPadding(5.0f);
    //As tall as the bar: 25 pt rasterizes about 33 px tall, and text is clipped to its label, so a 30 px label cuts off the tails of p, g and y
    barTitle->SetSize(glm::vec3(200.0f, 40.0f, 0.01f));
    _members->_bar->AddWidget(std::move(barTitle), 0);
    _members->_barTitle = _members->_bar->GetWidget<RetroFuturaGUI::Label>(0);

    std::unique_ptr<RetroFuturaGUI::Button> closeButton
    {
        std::make_unique<RetroFuturaGUI::Button>("PopupBarClose", &projection, &*_members->_bar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    closeButton->SetSize(glm::vec3(28.0f, 28.0f, 0.01f));
    closeButton->SetBackgroundImage("Resources/img/CloseIcon.svg");
    closeButton->SetBackgroundImagePadding(4.0f);
    closeButton->SetBackgroundColor(glm::vec4(1.0f, 0.1f, 0.1f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    closeButton->SetBackgroundColor(glm::vec4(1.0f, 0.2f, 0.2f, 0.45f), RetroFuturaGUI::ColorState::Hover);
    closeButton->SetBackgroundColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.6f), RetroFuturaGUI::ColorState::Clicked);
    closeButton->SetBorderWidth(0.0f);
    //Closing a popup without values dismisses it, like a menu bar's close button closes a window
    closeButton->Connect_OnClick([popup]() { popup->Dismiss(); }, false);
    _members->_bar->AddWidget(std::move(closeButton), 2);
    _members->_closeButton = _members->_bar->GetWidget<RetroFuturaGUI::Button>(2);

    rootLasagna->AttachWidget(0, 0, 0, &*_members->_bar, RetroFuturaGUI::SizingMode::FILL, 1, 3);

//Prompt
    _members->_prompt = std::make_unique<RetroFuturaGUI::Label>("PopupPrompt", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_prompt->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    _members->_prompt->SetText("Enter a name:", false);
    _members->_prompt->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_prompt->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_prompt->SetTextPadding(5.0f);
    _members->_prompt->SetSize(glm::vec3(440.0f, 30.0f, 0.01f));
    rootLasagna->AttachWidget(1, 0, 0, &*_members->_prompt, RetroFuturaGUI::SizingMode::FIXED, 1, 3);

//Text box
    _members->_nameTextBox = std::make_unique<RetroFuturaGUI::TextBox>("PopupNameTextBox", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_nameTextBox->SetSize(glm::vec3(440.0f, 44.0f, 0.01f));
    _members->_nameTextBox->SetCornerRadii(glm::vec4(10.0f));
    _members->_nameTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_nameTextBox->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_nameTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_nameTextBox->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_nameTextBox->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_nameTextBox->SetBorderWidth(2.0f);
    _members->_nameTextBox->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    _members->_nameTextBox->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_nameTextBox->SetTextPadding(5.0f);
    _members->_nameTextBox->SetPlaceholderText("Name...");
    _members->_nameTextBox->SetPlaceholderTextColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    rootLasagna->AttachWidget(2, 0, 0, &*_members->_nameTextBox, RetroFuturaGUI::SizingMode::FIXED, 1, 3);

//Buttons
    _members->_okButton = std::make_unique<RetroFuturaGUI::Button>("PopupOk", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_cancelButton = std::make_unique<RetroFuturaGUI::Button>("PopupCancel", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_anotherButton = std::make_unique<RetroFuturaGUI::Button>("PopupAnother", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);

    const std::pair<RetroFuturaGUI::Button*, std::string_view> buttons[]
    {
        { &*_members->_okButton, "OK" },
        { &*_members->_cancelButton, "Cancel" },
        { &*_members->_anotherButton, "Another" }
    };
    u32 column { 0 };

    for(const auto& [button, text] : buttons)
    {
        const u32 buttonColumn { column };
        ++column;

        if(!button)
            continue;

        button->SetSize(glm::vec3(130.0f, 44.0f, 0.01f));
        button->SetCornerRadii(glm::vec4(10.0f));
        button->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        button->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
        button->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
        button->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
        button->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        button->SetBorderWidth(2.0f);
        button->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
        button->SetText(text, false);
        button->SetTextAlignment(RetroFuturaGUI::TextAlignment::Center);
        rootLasagna->AttachWidget(3, buttonColumn, 0, button, RetroFuturaGUI::SizingMode::FIXED);
    }

    _members->_okButton->Connect_OnClick([this]() { on_okButton_click(); }, false);
    _members->_cancelButton->Connect_OnClick([this]() { on_cancelButton_click(); }, false);
    _members->_anotherButton->Connect_OnClick([this]() { on_anotherButton_click(); }, false);
}
