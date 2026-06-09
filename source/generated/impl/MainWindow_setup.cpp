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


    RetroFuturaGUI::FontManager::LoadFont("Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, BasicLatinFirst, BasicLatinLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, Latin1SupplementFirst, Latin1SupplementLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, HiraganaFirst, HiraganaLast);
    RetroFuturaGUI::FontManager::ExtendFontset("Noto Sans", "Noto Sans CJK JP", 25, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Regular, KatakanaFirst, KatakanaLast);
    _members->_window->SetWindowTitle(windowTitle, "Noto Sans");


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


    _members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::WindowBar::ElementType::Title);
    _members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::WindowBar::ElementType::Title);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.1f, 0.1f, 0.65f), RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.2f, 0.2f, 0.65f), RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.75f), RetroFuturaGUI::ColorState::Clicked, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.75f), RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.75f), RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.85f), RetroFuturaGUI::ColorState::Clicked, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.75f), RetroFuturaGUI::ColorState::Enabled, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.75f), RetroFuturaGUI::ColorState::Hover, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.85f), RetroFuturaGUI::ColorState::Clicked, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);



    RetroFuturaGUI::IdentityParams identityLasagna = { "testLasagna", this, RetroFuturaGUI::WidgetTypeID::Lasagna, window };
	RetroFuturaGUI::GeometryParams3D geometryLasagna = { ._Projection = projection, ._Position = glm::vec3(0.0f, 0.0f, 0.0f), ._Size = glm::vec3(resolution.x, resolution.y, projection.GetDepth()), ._Rotation = 0.0f };
	RetroFuturaGUI::AxisDefinition axisDefinition = 
	{
		{ 0.3f, 0.5f, 0.2f },
		{ 0.6f, 0.4f },
        { 0.0f }
	};

	_members->_testLasagna = std::make_unique<RetroFuturaGUI::Lasagna>(identityLasagna, geometryLasagna, axisDefinition);
std::string tempID = _members->_name +  "/testButton";
    RetroFuturaGUI::IdentityParams identityB = { tempID, this, RetroFuturaGUI::WidgetTypeID::Window, window };
	RetroFuturaGUI::GeometryParams3D geometryB = { ._Projection = projection, ._Position = glm::vec3(0.0f, 0.0f, 0.0f), ._Size = glm::vec3(300.0f, 90.0f, 0.01f), ._Rotation = 0.0f };
	RetroFuturaGUI::TextParams textParamsB = { "ボタン", "Noto Sans", glm::vec4(1.0f), glm::vec2(25.0f), RetroFuturaGUI::TextAlignment::CENTER, 5.0f };


	_members->_testButton = std::make_unique<RetroFuturaGUI::Button>(identityB, geometryB, textParamsB, 5.0f);


    if(frutiger)
    {
        
	_members->_testButton->SetCornerRadii(glm::vec4(45.0f));
	_members->_testButton->SetWindowBackgroundImageTextureID(_members->_window->GetBackgroundImageId());
	_members->_testButton->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Enabled);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Hover);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), RetroFuturaGUI::ColorState::Clicked);

    
    }
    else
    {

        std::vector<glm::vec4> testv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} ,  { 0.980f, 0.851f, 0.875f, 1.0f }
            , { 0.965f, 0.761f, 0.965f, 1.0f }, { 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.718f, 0.976f, 0.992f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }});
        _members->_testButton->SetCornerRadii(glm::vec4(20.0f));
        _members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        _members->_testButton->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
        _members->_testButton->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);

        _members->_testButton->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorState::Hover);
        _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorState::Clicked);


        //_members->_testButton->SetBorderGradientAnimationSpeed(0.0005f);
        _members->_testButton->SetBorderGradientRotationSpeed(2.5f);
        _members->_testButton->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);

    }


    //TextBox

    RetroFuturaGUI::IdentityParams identityTextBox = { "testTextBox", this, RetroFuturaGUI::WidgetTypeID::TextBox, window };
    RetroFuturaGUI::GeometryParams3D geometryTextBox = { ._Projection = projection, ._Position = glm::vec3(0.0f, -100.0f, 0.0f), ._Size = glm::vec3(300.0f, 90.0f, 0.01f), ._Rotation = 0.0f };
    RetroFuturaGUI::TextParams textParamsTextBox = { "Test...ンンン", "Noto Sans", glm::vec4(1.0f), glm::vec2(25.0f), RetroFuturaGUI::TextAlignment::LEFT, 5.0f };

    _members->_testTextBox = std::make_unique<RetroFuturaGUI::TextBox>(identityTextBox, geometryTextBox, textParamsTextBox, 5.0f);

    std::vector<glm::vec4> testtextv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} ,  { 0.980f, 0.851f, 0.875f, 1.0f }
        , { 0.965f, 0.761f, 0.965f, 1.0f }, { 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.718f, 0.976f, 0.992f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }});
    _members->_testTextBox->SetCornerRadii(glm::vec4(20.0f));
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Clicked);

    _members->_testTextBox->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBorderColors(testtextv, RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBorderColors(testtextv, RetroFuturaGUI::ColorState::Clicked);


    //_members->_testButton->SetBorderGradientAnimationSpeed(0.0005f);
    _members->_testTextBox->SetBorderGradientRotationSpeed(2.5f);
    _members->_testTextBox->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);


    _members->_testLasagna->AttachWidget(1, 0, 0, &*_members->_testTextBox, RetroFuturaGUI::SizingMode::FIXED);
    _members->_testLasagna->AttachWidget(1, 1, 0, &*_members->_testButton, RetroFuturaGUI::SizingMode::FIXED);

#ifdef DYNLIB_MODE
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testButton->GetName(), &*_members->_testButton);
#else
    _members->_testButton->Connect_OnClick([this]() { on_testButton_clicked(); }, false);
    _members->_testTextBox->Connect_OnTextChange([this]() { on_testTextBox_textChange(); }, false);
#endif

    //_members->_testButton->SetRotation(45.0f);

    _members->_window->SetLasagna(&*_members->_testLasagna);

}