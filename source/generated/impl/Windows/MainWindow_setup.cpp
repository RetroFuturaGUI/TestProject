#include "MainWindow.hpp"
#include "MainScene.hpp"
//#include "MenuBarScene.hpp"
#include "CustomMenuBarScene.hpp"
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
    //CustomMenuBarScene carries the title and the window controls now, so the window's own bar is
    //never created. ShowWindowBar is the only thing that builds one, and GetWindowBar() dereferences
    //it unguarded, so every call below had to go with it.
    //_members->_window->ShowWindowBar(true);
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
    
//Window::SetWindowTitle rather than the bar's: it sets the native title GLFW shows in the taskbar,
//and only forwards to the bar when one exists.
#if defined(TARGET_PLATFORM_LINUX)
    _members->_window->SetWindowTitle(windowTitle, "Noto Sans");
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_window->SetWindowTitle(windowTitle, "Arial");
#endif

//The window's own bar is gone, so all of its styling is dead. Kept commented rather than deleted, to
//make going back to it a matter of uncommenting this block and ShowWindowBar above.
    //_members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::Title);
    //_members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::CloseButton);
    //_members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
    //_members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
    //_members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::Background);
    //std::vector<glm::vec4>col1( {{ glm::vec4(1.0f, 0.1f, 0.1f, 0.65f) }} );
    //std::vector<glm::vec4>col2( {{ glm::vec4(1.0f, 0.2f, 0.2f, 0.65f) }} );
    //std::vector<glm::vec4>col3( {{ glm::vec4(1.0f, 0.3f, 0.3f, 0.75f) }} );
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col1.data(), col1.size()), RetroFuturaGUI::ColorState::Enabled);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col2.data(), col2.size()), RetroFuturaGUI::ColorState::Hover);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col3.data(), col3.size()), RetroFuturaGUI::ColorState::Clicked);

    //std::vector<glm::vec4>col4( {{ glm::vec4(0.5f, 0.5f, 0.5f, 0.75f) }} );
    //std::vector<glm::vec4>col5( {{ glm::vec4(0.7f, 0.7f, 0.7f, 0.75f) }} );
    //std::vector<glm::vec4>col6( {{ glm::vec4(0.8f, 0.8f, 0.8f, 0.85f) }} );
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col4.data(), col4.size()), RetroFuturaGUI::ColorState::Enabled);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col5.data(), col5.size()), RetroFuturaGUI::ColorState::Hover);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col6.data(), col6.size()), RetroFuturaGUI::ColorState::Clicked);

    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col4.data(), col4.size()), RetroFuturaGUI::ColorState::Enabled);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col5.data(), col5.size()), RetroFuturaGUI::ColorState::Hover);
    //_members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col6.data(), col6.size()), RetroFuturaGUI::ColorState::Clicked);

    //_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	//_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	//_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);


    //std::vector<glm::vec4>col8( {{ glm::vec4(0.5f, 0.0f, 1.0f, 1.0f) }} );
    //_members->_window->GetWindowBar().SetBackgroundColors(std::span<glm::vec4>(col8.data(), col8.size()));

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
//The docked menu bar goes first, because reservations are taken in insertion order and MainScene
//has to be fitted into whatever is left.
    //_members->_scenes.push_back(std::make_unique<MenuBarScene>(_members->_window.get()));
    _members->_scenes.push_back(std::make_unique<CustomMenuBarScene>(_members->_window.get()));
    _members->_scenes.push_back(std::make_unique<MainScene>(_members->_window.get()));


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
                _members->_scenes.remove_if([_closing](const std::unique_ptr<RetroFuturaGUI::ISceneHost>& _entry)
                    { return _entry.get() == _closing; });
            });
    }
}
