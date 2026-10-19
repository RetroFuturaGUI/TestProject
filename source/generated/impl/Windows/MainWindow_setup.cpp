#include "MainWindow.hpp"
#include "MainScene.hpp"
//#include "MenuBarScene.hpp"
#include "CustomMenuBarScene.hpp"
#include "EnvironmentScene.hpp"
#include "SecondaryWindow.hpp"
#include "TabWindow.hpp"
#include "NoteWindow.hpp"
#include "WindowTab.hpp"
#include "SceneLoader.hpp"
#include "FontManager.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include "Rectangle.hpp"
#include "UnicodeBlocks.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>
#include <print>

void TestProject::MainWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    bool frutiger = false;
    RetroFuturaGUI::FontManager::Init();

    _members = std::make_unique<MainWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, width, height);
    std::vector<glm::vec4> _windowBgColors { { 0.0f, 0.2f, 0.7f, 1.0f }, { 0.61f, 0.06f, 0.5f, 1.0f }, { 0.0f, 0.1f, 0.69f, 1.0f }};
    _members->_window->SetBackgroundColors(_windowBgColors, RetroFuturaGUI::ColorState::Enabled);
    _members->_window->SetBackgroundFillType(RetroFuturaGUI::FillType::LINEAR_GRADIENT);
    _members->_window->SetBackgroundGradientAnimationSpeed(0.002f);
    _members->_window->SetBackgroundGradientRotationSpeed(0.1f);
    static std::vector<f32> dotDiameters = { 5.0f, 0.0f,5.0f };
    _members->_window->SetBackgroundPrimaryRasterWidthTransfer(dotDiameters);
    _members->_window->SetBackgroundDotDistance(25.0f);
    _members->_window->SetBackgroundRasterDegree(35.0f);
    _members->_window->SetBackgroundPrimaryRasterColor(glm::vec4(0.6f, 0.6f, 0.6f, 0.8f));
    _members->_window->SetBackgroundRasterAnimationSpeed(-0.13f);
    _members->_window->SetBackgroundDotTransparencyTransfer(0.4f);
    static std::vector<f32> fogDensity = { 1.0f, 0.55f, 0.3f, 0.15f };
    _members->_window->SetBackgroundFogDensity(fogDensity);
    _members->_window->SetBackgroundFogAlpha(0.5f);
    _members->_window->SetBackgroundFogSpeed(0.12f);
    _members->_window->SetBackgroundFogClearing(0.1f);

    GLFWwindow* window = _members->_window->GetGlfwWindow();
    RetroFuturaGUI::Projection& projection = *_members->_window->GetProjection(); 
    glm::vec2 resolution = projection.GetResolution();

#if defined(TARGET_PLATFORM_LINUX)
    RetroFuturaGUI::FontManager::LoadFont("Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, BasicLatinFirst, BasicLatinLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, Latin1SupplementFirst, Latin1SupplementLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, HiraganaFirst, HiraganaLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, KatakanaFirst, KatakanaLast);
#elif defined(TARGET_PLATFORM_WINDOWS)
    RetroFuturaGUI::FontManager::LoadFont("Arial", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, BasicLatinFirst, BasicLatinLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Arial", "Arial", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, Latin1SupplementFirst, Latin1SupplementLast);
    //RetroFuturaGUI::FontManager::ExtendFontset("Yu Mincho", "Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, HiraganaFirst, HiraganaLast);
    //RetroFuturaGUI::FontManager::ExtendFontset("Yu Mincho", "Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, KatakanaFirst, KatakanaLast);
#endif
    
//This sets only the title the taskbar shows. The title drawn inside the window is the label in
//CustomMenuBarScene, which is set on its own.
    _members->_window->SetWindowTitle(windowTitle);

    if(frutiger)
    {
        std::string path = PlatformBridge::Paths::GetExecutablePath();
#if defined(_WIN32) || defined(_WIN64)
        path = path.substr(0, path.find_last_of(R"(\)"));
        path.append(R"(\Resources\img\FrutigerAero.png)");
#else
        path = path.substr(0, path.find_last_of(R"(/)"));
        path.append("/ShaderSource/");
#endif

      _members->_window->SetBackgroundImage(path);
    }



//Scenes own their own widgets; this window only decides which ones exist and in what order.
//Scenes draw in insertion order, so EnvironmentScene goes first to sit behind the other two. It is an
//overlay and reserves nothing, so going first doesn't take the menu bar's strip: docked scenes reserve
//in their own pass. Among the docked scenes the menu bar comes first, because reservations are taken in
//insertion order and MainScene has to be fitted into whatever is left.
    _members->_scenes.push_back(std::make_unique<EnvironmentScene>(_members->_window.get()));
    //_members->_scenes.push_back(std::make_unique<MenuBarScene>(_members->_window.get()));
    _members->_scenes.push_back(std::make_unique<CustomMenuBarScene>(_members->_window.get(), "CustomMenuBarScene", "Test"));
    //Kept as its own type, so the secondary window's video can be handed to it below and taken back when that window closes
    std::unique_ptr<MainScene> mainScene { std::make_unique<MainScene>(_members->_window.get()) };
    _members->_mainScene = mainScene.get();
    _members->_scenes.push_back(std::move(mainScene));


    for(const std::unique_ptr<RetroFuturaGUI::ISceneHost>& _host : _members->_scenes)
    {
        RetroFuturaGUI::Scene* _scene { _host->GetScene() };

        if(!_scene)
            continue;

        _members->_window->AddScene(_scene);

        //Closing a scene detaches it; dropping the host that owns it is this window's job, so
        //hand the loader a hook that erases it from the list above.
        RetroFuturaGUI::ISceneHost* _closing { _host.get() };
        RetroFuturaGUI::SceneLoader::SetReleaseHook(RetroFuturaGUI::SceneLoader::GetSceneID(_scene->GetName()),
            [this, _closing]()
            {
                //A closed MainScene must not be told about the video any more
                if(_closing == _members->_mainScene)
                    _members->_mainScene = nullptr;

                _members->_scenes.remove_if([_closing](const std::unique_ptr<RetroFuturaGUI::ISceneHost>& _entry)
                    { return _entry.get() == _closing; });
            });
    }

//ScrollViewScene has a window of its own, beside this one. 600 px fits its menu bar: title and menu take 200 px each, and the
//undock handle and the three window controls 40 px each.
    _members->_secondaryWindow = std::make_unique<SecondaryWindow>("RetroFuturaGUI ScrollView", 600, 720);

//The tab window holds the secondary window and a note window in its tabs. 640 px fits its menu bar, like the secondary window's.
    _members->_tabWindow = std::make_unique<TabWindow>("RetroFuturaGUI Tabs", 640, 720);
    _members->_noteWindow = std::make_unique<NoteWindow>("Notes", 600, 480);

    //Creating a window makes its GL context current, so this window's is made current again before its widgets are touched
    glfwMakeContextCurrent(window);

    RetroFuturaGUI::Window* secondaryWindow { _members->_secondaryWindow->GetWindow() };
    RetroFuturaGUI::Window* tabWindow { _members->_tabWindow->GetWindow() };
    RetroFuturaGUI::Window* noteWindow { _members->_noteWindow->GetWindow() };
    RetroFuturaGUI::WindowTab* windowTab { _members->_tabWindow->GetWindowTab() };

    if(!secondaryWindow)
        return;

    if(!tabWindow)
        return;

    if(!noteWindow)
        return;

    if(!windowTab)
        return;

    //Rounded corners with a thin frame, in the menu bars' border color. The corners where docked windows meet are squared, and a
    //window in a tab takes the tab's corners instead.
    for(RetroFuturaGUI::Window* framed : { _members->_window.get(), tabWindow, secondaryWindow, noteWindow })
    {
        if(!framed)
            continue;

        framed->SetCornerRadii(glm::vec4(12.0f));
        framed->SetBorderWidth(1.0f);
        framed->SetBorderColor(glm::vec4(0.35f, 0.35f, 0.45f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    }

    //Both ways of docking from the start: the tab window docks to this window's right edge, 8 px away, where it takes this
    //window's height, and the other two windows dock into its tabs. Dragging a tab out pulls its window out, and dragging a
    //window by its bar over the tab strip puts it back.
    _members->_window->SetDockingPadding(8.0f);
    _members->_window->DockWindow(tabWindow, RetroFuturaGUI::DockEdge::Right);
    windowTab->AddWindow(secondaryWindow);
    windowTab->AddWindow(noteWindow);

    if(!_members->_mainScene)
        return;

    //MainScene shows the sound of the video in the other window
    _members->_mainScene->SetVideo(_members->_secondaryWindow->GetVideo());
}
