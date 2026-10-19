#include "CustomMenuBarScene.hpp"
#include "CustomMenuBarScene_p.hpp"
#include "Window.hpp"
#include "Lasagna.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>

TestProject::CustomMenuBarScene::CustomMenuBarScene(RetroFuturaGUI::Window* parentWindow, std::string_view sceneName, std::string_view title)
{
    _members = std::make_unique<CustomMenuBarScene_p>();
    setup(parentWindow, sceneName, title);
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

void TestProject::CustomMenuBarScene::setup(RetroFuturaGUI::Window* parentWindow, std::string_view sceneName, std::string_view title)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection& projection { *parentWindow->GetProjection() };
    GLFWwindow* window { parentWindow->GetGlfwWindow() };

//The window's title bar: a MenuBar that reserves a strip across the top and carries the title, one
//menu and the window controls in its flex. The window draws no bar of its own.
//The bar lays its own slots out, so the root Lasagna only has to hand it the whole reserved strip.
    RetroFuturaGUI::AxisDefinition menuBarAxis
    {
        ._RowDefinition    = { 1.0f },
        ._ColumnDefinition = { 1.0f },
        ._LayerDefinition  = { 1.0f }
    };

    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene(sceneName, parentWindow);

    if(!_members->_scene)
        return;

    _members->_scene->SetLasagnaAxis(menuBarAxis, &projection);
    _members->_scene->SetReservedEdge(RetroFuturaGUI::DockEdge::Top, 40.0f);
    //While the window sits in a tab, the tab's field shows its title and close button instead, and the content takes the strip
    _members->_scene->SetHiddenInTab(true);

    RetroFuturaGUI::Lasagna* rootLasagna { _members->_scene->GetRootContainer<RetroFuturaGUI::Lasagna>() };

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
       undock handle and the three controls are squares of the bar's own height, which pins them to the right edge. */
    std::vector<RetroFuturaGUI::MenuBar::FlexDefinition> flexDefinition
    {
        //The title drags the window, with its whole docking group. The flag only takes on a Label, so the empty spacer cannot carry it.
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Auto,   ._Width = 0.0f, ._IsWindowDrag = true,  ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Auto,   ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Star,   ._Width = 1.0f, ._IsWindowDrag = false, ._IsWindowUndock = false },
        //The undock handle pulls the window out of its docking group and drags it alone
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = true  },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = false },
        { ._FlexSizing = RetroFuturaGUI::MenuBar::FlexSizing::Square, ._Width = 0.0f, ._IsWindowDrag = false, ._IsWindowUndock = false }
    };
    _members->_menuBar->SetFlexDefinition(flexDefinition);

//Title
    std::unique_ptr<RetroFuturaGUI::Label> menuBarLabel
    {
        std::make_unique<RetroFuturaGUI::Label>("CustomMenuBarLabel", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    menuBarLabel->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    menuBarLabel->SetText(title, false);
    menuBarLabel->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    menuBarLabel->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    menuBarLabel->SetTextPadding(5.0f);
    //As tall as the bar: 25 pt rasterizes about 33 px tall, and text is clipped to its label, so a 30 px label cuts off the tails of p, g and y
    menuBarLabel->SetSize(glm::vec3(200.0f, 40.0f, 0.01f));
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

//Undock handle
    //An icon rather than a button, because the drag would swallow a button's clicks, and the cell's hover color shows it can be grabbed
    std::unique_ptr<RetroFuturaGUI::SvgImage> undockHandle
    {
        std::make_unique<RetroFuturaGUI::SvgImage>("CustomMenuBarUndock", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window, "Resources/img/Undock.svg")
    };
    undockHandle->SetSize(glm::vec3(20.0f, 20.0f, 0.01f)); //the buttons' 28 px less their 4 px icon padding on each side
    _members->_menuBar->AddWidget(std::move(undockHandle), 3);
    _members->_undockHandle = _members->_menuBar->GetWidget<RetroFuturaGUI::SvgImage>(3);

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
    _members->_menuBar->AddWidget(std::move(buttonMinimize), 4);
    _members->_buttonMinimize = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(4);

    std::unique_ptr<RetroFuturaGUI::Button> buttonMaximize
    {
        std::make_unique<RetroFuturaGUI::Button>("CustomMenuBarMaximize", &projection, &*_members->_menuBar, RetroFuturaGUI::WidgetTypeID::MenuBar, window)
    };
    buttonMaximize->SetSize(glm::vec3(28.0f, 28.0f, 0.01f));
    //Maximize while the window is restored, WindowMode while it is maximized. The click handler swaps it.
    buttonMaximize->SetBackgroundImage(parentWindow->IsMaximized()
        ? "Resources/img/WindowMode.svg"
        : "Resources/img/Maximize.svg");
    buttonMaximize->SetBackgroundImagePadding(4.0f);
    //buttonMaximize->SetCornerRadii(glm::vec4(10.0f));
    buttonMaximize->SetBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.0f), RetroFuturaGUI::ColorState::Enabled);
    buttonMaximize->SetBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.35f), RetroFuturaGUI::ColorState::Hover);
    buttonMaximize->SetBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.55f), RetroFuturaGUI::ColorState::Clicked);
    buttonMaximize->SetBorderWidth(0.0f);
    //The button is captured so the icon can follow the state; it outlives the callback, being owned by
    //the flex slot the callback is reached through.
    RetroFuturaGUI::Button* maximizeButton { buttonMaximize.get() };
    buttonMaximize->Connect_OnClick([parentWindow, maximizeButton]()
        {
            if(!parentWindow)
                return;

            if(!maximizeButton)
                return;

            //The state is read before toggling, because on Linux the window manager applies a maximize
            //later, and asking right after the toggle can still return the old state.
            const bool wasMaximized { parentWindow->IsMaximized() };
            parentWindow->ToggleMaximize();

            //Reloads the file on each click. These icons are a few hundred bytes, and a window is not
            //maximized often enough for caching them to be worth the two extra members.
            maximizeButton->SetBackgroundImage(wasMaximized
                ? "Resources/img/Maximize.svg"
                : "Resources/img/WindowMode.svg");
            maximizeButton->SetBackgroundImagePadding(4.0f);
        }, false);
    _members->_menuBar->AddWidget(std::move(buttonMaximize), 5);
    _members->_buttonMaximize = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(5);

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
    _members->_menuBar->AddWidget(std::move(buttonClose), 6);
    _members->_buttonClose = _members->_menuBar->GetWidget<RetroFuturaGUI::Button>(6);

    rootLasagna->AttachWidget(0, 0, 0, &*_members->_menuBar, RetroFuturaGUI::SizingMode::FILL);

//Corners
    //The bar lies over the window's top corners, so it rounds its own like the window's, and squares them with the window's
    //where docked windows meet. Each frame, since docking can change them any time.
    _members->_scene->Connect_OnUpdate([this, parentWindow]()
        {
            if(!parentWindow)
                return;

            if(!_members)
                return;

            if(!_members->_menuBar)
                return;

            const glm::vec4 windowRadii { parentWindow->GetDrawnCornerRadii() };
            _members->_menuBar->SetCornerRadii(glm::vec4(windowRadii.x, windowRadii.y, 0.0f, 0.0f));
        }, false);

//Undock handle look
    //The bar disables the undock handle while the window is docked to nothing. Its paths then turn gray, and get their
    //own white back once the window is docked again.
    _members->_scene->Connect_OnUpdate([this]()
        {
            if(!_members)
                return;

            if(!_members->_undockHandle)
                return;

            const bool isEnabled { _members->_undockHandle->IsEnabled() };

            //Only on a change, since every path color rasterizes the icon again
            if(isEnabled == _members->_undockHandleLooksEnabled)
                return;

            _members->_undockHandleLooksEnabled = isEnabled;

            for(const RetroFuturaGUI::SvgPathInfo& path : _members->_undockHandle->GetNamedPaths())
            {
                if(isEnabled)
                {
                    _members->_undockHandle->ClearPathFill(path.name);
                    continue;
                }

                _members->_undockHandle->SetPathFill(path.name, RetroFuturaGUI::SvgPathFill
                {
                    .fillType = RetroFuturaGUI::FillType::SOLID,
                    .colors = { glm::vec4(0.4f, 0.4f, 0.45f, 1.0f) },
                    .gradientDegree = 0.0f,
                    .gradientOffset = 0.0f,
                    .gradientAnimationSpeed = 0.0f,
                    .gradientRotationSpeed = 0.0f
                });
            }
        }, false);
}
