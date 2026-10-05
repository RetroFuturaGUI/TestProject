#include "CustomMenuBarScene.hpp"
#include "CustomMenuBarScene_p.hpp"
#include "Window.hpp"
#include "Lasagna.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>

TestProject::CustomMenuBarScene::CustomMenuBarScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<CustomMenuBarScene_p>();
    setup(parentWindow);
}

TestProject::CustomMenuBarScene::~CustomMenuBarScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(_members && _members->_scene)
        RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::CustomMenuBarScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::CustomMenuBarScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection& projection { *parentWindow->GetProjection() };
    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//A menu bar built out of a MenuBar widget rather than the window's own WindowBar: it reserves a strip
//across the top and carries the title, one menu and the window controls in its flex.
//The bar lays its own slots out, so the root Lasagna only has to hand it the whole reserved strip.
    RetroFuturaGUI::AxisDefinition menuBarAxis
    {
        ._RowDefinition    = { 1.0f },
        ._ColumnDefinition = { 1.0f },
        ._LayerDefinition  = { 1.0f }
    };

    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("CustomMenuBarScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(menuBarAxis, &projection);
    _members->_scene->SetReservedEdge(RetroFuturaGUI::DockEdge::Top, 40.0f);

    RetroFuturaGUI::Lasagna* rootLasagna { _members->_scene->GetRootLasagna() };

    if(!rootLasagna)
        return;

//MenuBar
    _members->_menuBar = std::make_unique<RetroFuturaGUI::MenuBar>("CustomMenuBar", &projection, rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    //Top also decides the slots run along X. The Lasagna sets the final position, so the margin and
    //alignment the docking would apply are left at their defaults here.
    _members->_menuBar->SetDockingEdge(RetroFuturaGUI::MenuBar::DockingEdge::Top);
    _members->_menuBar->SetBackgroundColor(glm::vec4(0.08f, 0.08f, 0.12f, 0.9f), RetroFuturaGUI::ColorState::Enabled);
    _members->_menuBar->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_menuBar->SetBorderColor(glm::vec4(0.35f, 0.35f, 0.45f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_menuBar->SetBorderWidth(1.0f);

    //Item colors are shared by every slot; only the slot under the cursor draws the hover/click ones.
    _members->_menuBar->SetItemBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_menuBar->SetItemBackgroundColor(glm::vec4(0.25f, 0.25f, 0.35f, 0.9f), RetroFuturaGUI::ColorState::Hover);
    _members->_menuBar->SetItemBackgroundColor(glm::vec4(0.35f, 0.35f, 0.5f, 0.95f), RetroFuturaGUI::ColorState::Clicked);
    _members->_menuBar->SetItemBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.6f), RetroFuturaGUI::ColorState::Disabled);
    //Every state a slot can draw in needs its own color: MenuBar starts these vectors empty, and an
    //empty one is simply not pushed, so an unset state would keep the colors of the previous one.
    _members->_menuBar->SetItemBorderColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_menuBar->SetItemBorderColor(glm::vec4(0.5f, 0.5f, 0.65f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_menuBar->SetItemBorderColor(glm::vec4(0.6f, 0.6f, 0.8f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_menuBar->SetItemBorderColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_menuBar->SetItemBorderWidth(1.0f);

    _members->_menuBar->EnableSeparatorLines(true);
    _members->_menuBar->SetSeparatorLinesThickness(1.0f);
    _members->_menuBar->SetSeparatorLinesColor(glm::vec4(0.4f, 0.4f, 0.5f, 0.8f), RetroFuturaGUI::ColorState::Enabled);
    _members->_menuBar->SetSeparatorLinesColor(glm::vec4(0.25f, 0.25f, 0.3f, 0.8f), RetroFuturaGUI::ColorState::Disabled);

    /* The cells have to exist before anything can be put in one, and the definitions are what create
       them. Title and menu take their content's width, the spacer soaks up whatever is left, and the
       three controls are squares of the bar's own height, which pins them to the right edge. */
    std::vector<RetroFuturaGUI::MenuBar::FlexDefinition> flexDefinition
    {
        //The title drags the window. The flag only takes on a Label, so the empty spacer cannot carry it.
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Auto,   ._Width = 0.0f, ._IsWindowDrag = true  },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Auto,   ._Width = 0.0f, ._IsWindowDrag = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Star,   ._Width = 1.0f, ._IsWindowDrag = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false }
    };
    _members->_menuBar->SetFlexDefinition(flexDefinition);

//Title
    std::unique_ptr<RetroFuturaGUI::Label> menuBarLabel
    {
        std::make_unique<RetroFuturaGUI::Label>("CustomMenuBarLabel", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    menuBarLabel->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    menuBarLabel->SetText("Custom MenuBar Scene", false);
    menuBarLabel->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    menuBarLabel->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    menuBarLabel->SetTextPadding(5.0f);
    menuBarLabel->SetSize(glm::vec3(200.0f, 30.0f, 0.01f));
    _members->_menuBar->AddWidget(std::move(menuBarLabel), 0);
    _members->_menuBarLabel = _members->_menuBar->GetWidget<RetroFuturaGUI::Label>(0);

//Menu
    std::unique_ptr<RetroFuturaGUI::ColorPreview> colorPreview
    {
        std::make_unique<RetroFuturaGUI::ColorPreview>("CustomMenuBarColorPreview", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    colorPreview->SetPreviewColor(glm::vec4(0.5f, 0.0f, 1.0f, 0.8f));
    colorPreview->SetSize(glm::vec3(200.0f, 30.0f, 0.01f));

    _members->_menuBar->AddWidget(std::move(colorPreview), 1);
    _members->_colorPreview = _members->_menuBar->GetWidget<RetroFuturaGUI::ColorPreview>(1);

//Window controls
    std::unique_ptr<RetroFuturaGUI::Button> buttonMinimize
    {
        std::make_unique<RetroFuturaGUI::Button>("CustomMenuBarMinimize", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    //The icon is the background image, and the shader blends it under the background color by that
    //color's alpha: 0 shows the icon untouched, higher values wash it with the color. So the enabled
    //state is fully transparent and hover/click tint the icon instead of hiding it.
    buttonMinimize->SetSize(glm::vec3(28.0f, 28.0f, 0.01f));
    buttonMinimize->SetBackgroundImage("Resources/img/Minimize.svg");
    buttonMinimize->SetBackgroundImagePadding(4.0f);
    //buttonMinimize->SetCornerRadii(glm::vec4(10.0f));
    buttonMinimize->SetBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    buttonMinimize->SetBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.35f), RetroFuturaGUI::ColorState::Hover);
    buttonMinimize->SetBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.55f), RetroFuturaGUI::ColorState::Clicked);
    buttonMinimize->SetBorderWidth(0.0f);
    buttonMinimize->Connect_OnClick([window]() { glfwIconifyWindow(window); }, false);
    _members->_menuBar->AddWidget(std::move(buttonMinimize), 3);
    _members->_buttonMinimize = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(3);

    std::unique_ptr<RetroFuturaGUI::Button> buttonMaximize
    {
        std::make_unique<RetroFuturaGUI::Button>("CustomMenuBarMaximize", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    buttonMaximize->SetSize(glm::vec3(28.0f, 28.0f, 0.01f));
    //Maximize while the window is restored, WindowMode while it is maximized. The click handler swaps it.
    buttonMaximize->SetBackgroundImage(glfwGetWindowAttrib(window, GLFW_MAXIMIZED) == GLFW_TRUE
        ? "Resources/img/WindowMode.svg"
        : "Resources/img/Maximize.svg");
    buttonMaximize->SetBackgroundImagePadding(4.0f);
    //buttonMaximize->SetCornerRadii(glm::vec4(10.0f));
    buttonMaximize->SetBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    buttonMaximize->SetBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.35f), RetroFuturaGUI::ColorState::Hover);
    buttonMaximize->SetBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.55f), RetroFuturaGUI::ColorState::Clicked);
    buttonMaximize->SetBorderWidth(0.0f);
    //GLFW is asked directly, because the window's own maximize toggle is not part of its public surface.
    //The button is captured so the icon can follow the state; it outlives the callback, being owned by
    //the flex slot the callback is reached through.
    RetroFuturaGUI::Button* maximizeButton { buttonMaximize.get() };
    buttonMaximize->Connect_OnClick([window, maximizeButton]()
        {
            const bool wasMaximized { glfwGetWindowAttrib(window, GLFW_MAXIMIZED) == GLFW_TRUE };

            if(wasMaximized)
                glfwRestoreWindow(window);
            else
                glfwMaximizeWindow(window);

            if(!maximizeButton)
                return;

            //Reloads the file on each click. These icons are a few hundred bytes, and a window is not
            //maximized often enough for caching them to be worth the two extra members.
            maximizeButton->SetBackgroundImage(wasMaximized
                ? "Resources/img/Maximize.svg"
                : "Resources/img/WindowMode.svg");
            maximizeButton->SetBackgroundImagePadding(4.0f);
        }, false);
    _members->_menuBar->AddWidget(std::move(buttonMaximize), 4);
    _members->_buttonMaximize = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(4);

    std::unique_ptr<RetroFuturaGUI::Button> buttonClose
    {
        std::make_unique<RetroFuturaGUI::Button>("CustomMenuBarClose", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    buttonClose->SetSize(glm::vec3(28.0f, 28.0f, 0.01f));
    buttonClose->SetBackgroundImage("Resources/img/CloseIcon.svg");
    buttonClose->SetBackgroundImagePadding(4.0f);
    //buttonClose->SetCornerRadii(glm::vec4(10.0f));
    buttonClose->SetBackgroundColor(glm::vec4(1.0f, 0.1f, 0.1f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    buttonClose->SetBackgroundColor(glm::vec4(1.0f, 0.2f, 0.2f, 0.45f), RetroFuturaGUI::ColorState::Hover);
    buttonClose->SetBackgroundColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.6f), RetroFuturaGUI::ColorState::Clicked);
    buttonClose->SetBorderWidth(0.0f);
    buttonClose->Connect_OnClick([window]() { glfwSetWindowShouldClose(window, GLFW_TRUE); }, false);
    _members->_menuBar->AddWidget(std::move(buttonClose), 5);
    _members->_buttonClose = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(5);

    rootLasagna->AttachWidget(0, 0, 0, &*_members->_menuBar, RetroFuturaGUI::SizingMode::FILL);
}
