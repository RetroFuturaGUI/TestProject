#include "MainWindow.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "FontManager.hpp"
#include "UnicodeBlocks.hpp"

#ifdef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

#endif

void TestProject::MainWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    bool frutiger = false;
    RetroFuturaGUI::FontManager::Init();

    _members = std::make_unique<MainWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, width, height);


    GLFWwindow* window = _members->_window->GetGlfwWindow();
    RetroFuturaGUI::Projection& projection = *_members->_window->GetProjection(); 
    glm::vec2 resolution = projection.GetResolution();
    _members->_window->ShowWindowBar(true);
#if defined(TARGET_PLATFORM_LINUX)
    RetroFuturaGUI::FontManager::LoadFont("Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, BasicLatinFirst, BasicLatinLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, Latin1SupplementFirst, Latin1SupplementLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, HiraganaFirst, HiraganaLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, KatakanaFirst, KatakanaLast);
#elif defined(TARGET_PLATFORM_WINDOWS)
    RetroFuturaGUI::FontManager::LoadFont("Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, BasicLatinFirst, BasicLatinLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Yu Mincho", "Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, Latin1SupplementFirst, Latin1SupplementLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Yu Mincho", "Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, HiraganaFirst, HiraganaLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Yu Mincho", "Yu Mincho", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, KatakanaFirst, KatakanaLast);
#endif
    
#if defined(TARGET_PLATFORM_LINUX)
    _members->_window->GetWindowBar().SetWindowTitle(windowTitle, "Noto Sans");
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_window->GetWindowBar().SetWindowTitle(windowTitle, "Yu Mincho");
#endif
    _members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::CloseButton);
    _members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
    _members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
    _members->_window->GetWindowBar().EnableElement(RetroFuturaGUI::WindowBar::ElementType::Background);
    std::vector<glm::vec4>col1( {{ glm::vec4(1.0f, 0.1f, 0.1f, 0.65f) }} );
    std::vector<glm::vec4>col2( {{ glm::vec4(1.0f, 0.2f, 0.2f, 0.65f) }} );
    std::vector<glm::vec4>col3( {{ glm::vec4(1.0f, 0.3f, 0.3f, 0.75f) }} );
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col1.data(), col1.size()), RetroFuturaGUI::ColorState::Enabled);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col2.data(), col2.size()), RetroFuturaGUI::ColorState::Hover);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::CloseButton, std::span<glm::vec4>(col3.data(), col3.size()), RetroFuturaGUI::ColorState::Clicked);
	
    std::vector<glm::vec4>col4( {{ glm::vec4(0.5f, 0.5f, 0.5f, 0.75f) }} );
    std::vector<glm::vec4>col5( {{ glm::vec4(0.7f, 0.7f, 0.7f, 0.75f) }} );
    std::vector<glm::vec4>col6( {{ glm::vec4(0.8f, 0.8f, 0.8f, 0.85f) }} );
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col4.data(), col4.size()), RetroFuturaGUI::ColorState::Enabled);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col5.data(), col5.size()), RetroFuturaGUI::ColorState::Hover);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MaximizeButton, std::span<glm::vec4>(col6.data(), col6.size()), RetroFuturaGUI::ColorState::Clicked);
	
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col4.data(), col4.size()), RetroFuturaGUI::ColorState::Enabled);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col5.data(), col5.size()), RetroFuturaGUI::ColorState::Hover);
    _members->_window->GetWindowBar().SetButtonBackgroundColors(RetroFuturaGUI::WindowBar::ElementType::MinimizeButton, std::span<glm::vec4>(col6.data(), col6.size()), RetroFuturaGUI::ColorState::Clicked);
	
    _members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
    

    std::vector<glm::vec4>col8( {{ glm::vec4(0.5f, 0.0f, 1.0f, 1.0f) }} );
    _members->_window->GetWindowBar().SetBackgroundColors(std::span<glm::vec4>(col8.data(), col8.size()));

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


    //Lasagna
   RetroFuturaGUI::AxisDefinition axisDefinition = 
	{
		{ 0.3f, 0.5f, 0.2f },
		{ 0.6f, 0.4f },
        { 0.01f }
	};

	_members->_testLasagna = std::make_unique<RetroFuturaGUI::Lasagna>("testLasagne", &projection, nullptr, RetroFuturaGUI::WidgetTypeID::Lasagna, window, &axisDefinition);
    
    //Button
    _members->_testButton = std::make_unique<RetroFuturaGUI::Button>("TestButton", static_cast<RetroFuturaGUI::Projection*>(&projection), _members->_testLasagna.get(), RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testButton->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testButton->SetSize(glm::vec3(300.0f, 90.0f, 0.01f));
    _members->_testButton->SetRotation(0.0f);
    std::vector<glm::vec4> testv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} ,  { 0.980f, 0.851f, 0.875f, 1.0f }
            , { 0.965f, 0.761f, 0.965f, 1.0f }, { 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.718f, 0.976f, 0.992f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }});
    _members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testButton->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_testButton->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_testButton->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);

    _members->_testButton->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorState::Hover);
    _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorState::Clicked);

    //_members->_testButton->SetBorderGradientAnimationSpeed(0.0005f);
    _members->_testButton->SetBorderGradientRotationSpeed(5.0f);
    _members->_testButton->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testButton->SetBorderWidth(5.0f);
    _members->_testButton->SetCornerRadii(glm::vec4(20.0f));
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testButton->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testButton->SetFontFamily("Yu Mincho", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testButton->SetText("ボタン");
    _members->_testButton->SetTextAlignment(RetroFuturaGUI::TextAlignment::Center);
    _members->_testButton->SetTextPadding(5.0f);

    /*if(frutiger)
    {  
	_members->_testButton->SetCornerRadii(glm::vec4(45.0f));
	_members->_testButton->SetWindowBackgroundImageTextureID(_members->_window->GetBackgroundImageId());
	_members->_testButton->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Enabled);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Hover);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), RetroFuturaGUI::ColorState::Clicked);    
    }*/


    //TextBox
    _members->_testTextBox = std::make_unique<RetroFuturaGUI::TextBox>("TestTextBox", static_cast<RetroFuturaGUI::Projection*>(&projection), _members->_testLasagna.get(), RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testTextBox->SetPosition(glm::vec3(0.0f, -100.0f, 0.0f));
    _members->_testTextBox->SetSize(glm::vec3(300.0f, 50.0f, 0.01f));
    _members->_testTextBox->SetRotation(0.0f);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_testTextBox->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);

    std::vector<glm::vec4> testtextv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} ,  { 0.980f, 0.851f, 0.875f, 1.0f }
        , { 0.965f, 0.761f, 0.965f, 1.0f }, { 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.718f, 0.976f, 0.992f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }});
    _members->_testTextBox->SetCornerRadii(glm::vec4(15.0f));
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Clicked);

    _members->_testTextBox->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBorderColors(testtextv, RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBorderColors(testtextv, RetroFuturaGUI::ColorState::Clicked);


    //_members->_testButton->SetBorderGradientAnimationSpeed(0.0005f);
    _members->_testTextBox->SetBorderGradientRotationSpeed(5.0f);
    _members->_testTextBox->SetBorderWidth(2.0f);
    _members->_testTextBox->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testTextBox->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testTextBox->SetFontFamily("Yu Mincho", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testTextBox->SetText("Test TextBox...ンンン");
    _members->_testTextBox->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testTextBox->SetTextPadding(5.0f);
    //_members->_testTextBox->SetCaretColors(testtextv);
    _members->_testTextBox->SetCaretGradientAnimationSpeed(5.0f);
    _members->_testTextBox->SetCaretFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);


    //Label
    _members->_testLabel = std::make_unique<RetroFuturaGUI::Label>("TestLabel", static_cast<RetroFuturaGUI::Projection*>(&projection), _members->_testLasagna.get(), RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testLabel->SetPosition(glm::vec3(0.0f, -100.0f, 0.0f));
    _members->_testLabel->SetSize(glm::vec3(300.0f, 90.0f, 0.01f));
    _members->_testLabel->SetRotation(0.0f);
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testLabel->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testLabel->SetFontFamily("Yu Mincho", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testLabel->SetText("Test Label");
    _members->_testLabel->SetTextAlignment(RetroFuturaGUI::TextAlignment::Center);
    _members->_testLabel->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testLabel->SetTextPadding(5.0f);
    

    //Garnish lasagna
    _members->_testLasagna->AttachWidget(0, 0, 0, &*_members->_testLabel, RetroFuturaGUI::SizingMode::FIXED);
    _members->_testLasagna->AttachWidget(1, 0, 0, &*_members->_testTextBox, RetroFuturaGUI::SizingMode::FIXED);
    _members->_testLasagna->AttachWidget(1, 1, 0, &*_members->_testButton, RetroFuturaGUI::SizingMode::FIXED);


#ifdef DYNLIB_MODE
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testButton->GetName(), &*_members->_testButton);
#else
    _members->_testButton->Connect_OnClick([this]() { on_testButton_clicked(); }, false);
    _members->_testTextBox->Connect_OnTextChange([this]() { on_testTextBox_textChange(); }, false);
    _members->_testTextBox->Connect_OnEnterPressed([this]() { on_testTextBox_enterPressed(); }, false);
    _members->_testTextBox->Connect_OnEnterReleased([this]() { on_testTextBox_enterReleased(); }, false);
#endif

    //_members->_testButton->SetRotation(45.0f);

    _members->_window->SetLasagna(&*_members->_testLasagna);

}