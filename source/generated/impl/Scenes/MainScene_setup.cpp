#include "MainScene.hpp"
#include "MainScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include "IDropDown.hpp"
#include "IRangedValue.hpp"
#include "Rectangle.hpp"
#include "ResourceManager.hpp"
#include "SvgTexture.hpp"
#include "UnicodeBlocks.hpp"
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>
#include <print>

#ifdef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

#endif

TestProject::MainScene::MainScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<MainScene_p>();
    setup(parentWindow);
}

TestProject::MainScene::~MainScene()
{
    //Unregister before the scene is freed!
    if(_members && _members->_scene)
        RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::MainScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

void TestProject::MainScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection& projection { *parentWindow->GetProjection() };
    GLFWwindow* window { parentWindow->GetGlfwWindow() };

    //Lasagna
   RetroFuturaGUI::AxisDefinition axisDefinition = 
	{
		{ 0.1f, 0.15f, 0.25f, 0.4f, 0.1f }, //row
		{ 0.083f, 0.418f, 0.418f, 0.083f }, //col
        { 0.05f, 0.05 } //layer
	};


	_members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("MainScene", parentWindow);

	if(!_members->_scene)
		return;

	_members->_scene->SetLasagnaAxis(axisDefinition, &projection);

	//Aliases the scene's root Lasagna, which outlives this function - the widgets below are parented to it and attached into its cells.
	RetroFuturaGUI::Lasagna* _rootLasagna { _members->_scene->GetRootLasagna() };
    
    //Button
    _members->_testButton = std::make_unique<RetroFuturaGUI::Button>("TestButton", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testButton->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testButton->SetSize(glm::vec3(200.0f, 90.0f, 0.01f));
    _members->_testButton->SetRotation(glm::vec3(0.0f));
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
    _members->_testButton->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testButton->SetText("Button", false);
    _members->_testButton->SetTextAlignment(RetroFuturaGUI::TextAlignment::Center);
    _members->_testButton->SetTextPadding(5.0f);

    /*if(frutiger)
    {  
	_members->_testButton->SetCornerRadii(glm::vec4(45.0f));
	_members->_testButton->SetWindowBackgroundImageTextureID(parentWindow->GetBackgroundImageId());
	_members->_testButton->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Enabled);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), RetroFuturaGUI::ColorState::Hover);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), RetroFuturaGUI::ColorState::Clicked);    
    }*/


    //TextBox
    _members->_testTextBox = std::make_unique<RetroFuturaGUI::TextBox>("TestTextBox", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testTextBox->SetPosition(glm::vec3(0.0f, -100.0f, 0.0f));
    _members->_testTextBox->SetSize(glm::vec3(300.0f, 50.0f, 0.01f));
    _members->_testTextBox->SetRotation(glm::vec3(0.0f));
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
    _members->_testTextBox->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_testTextBox->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);

    std::vector<glm::vec4> testtextv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.980f, 0.851f, 0.875f, 1.0f }
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
    _members->_testTextBox->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testTextBox->SetValue(std::string_view(""));
    _members->_testTextBox->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testTextBox->SetTextPadding(5.0f);
    _members->_testTextBox->SetPlaceholderText("Placeholder Text...");
    _members->_testTextBox->SetPlaceholderTextColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    _members->_testTextBox->SetCaretColors(testtextv);
    _members->_testTextBox->SetCaretGradientAnimationSpeed(5.0f);
    _members->_testTextBox->SetCaretFillType(RetroFuturaGUI::FillType::LINEAR_GRADIENT);
    _members->_testTextBox->SetCaretGradientAnimationSpeed(0.0105f);
    _members->_testTextBox->SetCaretBlinkTime(750.0f);
    _members->_testTextBox->SetDecimalPrecision(-1);

    std::vector<glm::vec4> testTextSelectColor = std::vector<glm::vec4>({{ 0.0f, 0.1f, 0.6f, 1.0f}, { 0.6f, 0.3f, 0.3f, 1.0f},  { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.6f, 0.3f, 0.3f, 1.0f } });
    _members->_testTextBox->SetSelectedAreaColors(testTextSelectColor);
    _members->_testTextBox->SetSelectedAreaFillType(RetroFuturaGUI::FillType::LINEAR_GRADIENT);
    _members->_testTextBox->SetSelectedAreaGradientAnimationSpeed(0.0105f);
    _members->_testTextBox->SetSelectedAreaGradientRotationSpeed(1.0f);
    _members->_testTextBox->SetSelectedAreaCornerRadii(glm::vec4(10.0f));

    //Label
    _members->_testLabel = std::make_unique<RetroFuturaGUI::Label>("TestLabel", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testLabel->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testLabel->SetSize(glm::vec3(600.0f, 90.0f, 0.01f));
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testLabel->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testLabel->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testLabel->SetText("RetroFuturaGUI Test", false);
    _members->_testLabel->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testLabel->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testLabel->SetTextPadding(5.0f);
    
//RadioButtonLabel
    _members->_testRadioButtonText = std::make_unique<RetroFuturaGUI::Label>("TestRadioButtonLabel", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testRadioButtonText->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testRadioButtonText->SetSize(glm::vec3(600.0f, 90.0f, 0.01f));
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testRadioButtonText->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testRadioButtonText->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testRadioButtonText->SetText("Radio Button", false);
    _members->_testRadioButtonText->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testRadioButtonText->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButtonText->SetTextPadding(5.0f);

//RadioButtonLabel2
    _members->_testRadioButtonText2 = std::make_unique<RetroFuturaGUI::Label>("TestRadioButtonLabel2", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testRadioButtonText2->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testRadioButtonText2->SetSize(glm::vec3(600.0f, 90.0f, 0.01f));
#if defined(TARGET_PLATFORM_LINUX)
    _members->_testRadioButtonText2->SetFontFamily("Noto Sans", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#elif defined(TARGET_PLATFORM_WINDOWS)
    _members->_testRadioButtonText2->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
#endif
    _members->_testRadioButtonText2->SetText("Radio Button 2", false);
    _members->_testRadioButtonText2->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testRadioButtonText2->SetTextColor(glm::vec4(1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButtonText2->SetTextPadding(5.0f);

//Image
    _members->_testImage = std::make_unique<RetroFuturaGUI::Image>("TestImage", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window, "Resources/img/AlphaTest.png");
    _members->_testImage->SetSize(glm::vec3(300.0f, 90.0f, 0.01f));
    _members->_testImage->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
   // _members->_testImage->SetRotation(0.0f);
    
//Model
    _members->_testModel = std::make_unique<RetroFuturaGUI::Model>("TestModel", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testModel->LoadModel("Resources/cat/12222_Cat_v1_l3.obj");
    _members->_testModel->SetSize(glm::vec3(5.0f, 5.0f, 5.0f));
    _members->_testModel->SetRotation({ -90.0f, 0.0f, 00.0f });

//SvgImage
    _members->_testSvgImage = std::make_unique<RetroFuturaGUI::SvgImage>("TestSvgImage", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window, "Resources/img/BackgroundElement.svg");
    _members->_testSvgImage->SetSize(glm::vec3(300.0f, 90.0f, 0.01f));
    _members->_testSvgImage->SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
    

    RetroFuturaGUI::SvgPathFill fill
    {
        .fillType = RetroFuturaGUI::FillType::LINEAR_GRADIENT,
        .colors = { { 0.9f, 0.9f, 0.9f, 0.7f } },
        .gradientAnimationSpeed = 0.02f,
        .gradientRotationSpeed = 5.0f
    };

    for(auto& str : _members->_testSvgImage->GetNamedPaths())
    {
        _members->_testSvgImage->SetPathFill(str.name, fill);
    }

//CheckBox
    _members->_testCheckBox = std::make_unique<RetroFuturaGUI::CheckBox>("TextCheckBox", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    
    _members->_testCheckBox->SetSize({35.0f, 35.0f, 0.05f});

    std::vector<glm::vec4> _chbge( { glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) });
    std::vector<glm::vec4> _chbgd( { glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) });
    std::vector<glm::vec4> _chbgc( { glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) });
    std::vector<glm::vec4> _chbgh( { glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) });
    std::vector<glm::vec4> _chie( { glm::vec4(0.25f, 0.25f, 0.8f, 1.0f) });
    std::vector<glm::vec4> _chid( { glm::vec4(0.1f, 0.1f, 0.45f, 1.0f) });
    std::vector<glm::vec4> _chic( { glm::vec4(0.3f, 0.3f, 0.9f, 1.0f) });
    std::vector<glm::vec4> _chih( { glm::vec4(0.4f, 0.4f, 1.0f, 1.0f) });
    std::vector<glm::vec4> _chce( { glm::vec4(0.7f, 0.7f, 0.7f, 1.0f) });
    std::vector<glm::vec4> _chcd( { glm::vec4(0.3f, 0.3f, 0.3f, 1.0f) });
    std::vector<glm::vec4> _chcc( { glm::vec4(0.85f, 0.85f, 0.85f, 1.0f) });
    std::vector<glm::vec4> _chch( { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) });
    std::vector<glm::vec4> _chboe( { glm::vec4(0.7f, 0.7f, 0.7f, 1.0f) });
    std::vector<glm::vec4> _chbod( { glm::vec4(0.3f, 0.3f, 0.3f, 1.0f) });
    std::vector<glm::vec4> _chboc( { glm::vec4(0.85f, 0.85f, 0.85f, 1.0f) });
    std::vector<glm::vec4> _chboh( { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) });
    
    _members->_testCheckBox->SetCheckmarkColors(_chce, RetroFuturaGUI::ColorState::Enabled);
    _members->_testCheckBox->SetCheckmarkColors(_chcd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testCheckBox->SetCheckmarkColors(_chcc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testCheckBox->SetCheckmarkColors(_chch, RetroFuturaGUI::ColorState::Hover);
    _members->_testCheckBox->SetInherietColors(_chie, RetroFuturaGUI::ColorState::Enabled);
    _members->_testCheckBox->SetInherietColors(_chid, RetroFuturaGUI::ColorState::Disabled);
    _members->_testCheckBox->SetInherietColors(_chic, RetroFuturaGUI::ColorState::Clicked);
    _members->_testCheckBox->SetInherietColors(_chih, RetroFuturaGUI::ColorState::Hover);
    _members->_testCheckBox->SetBackgroundColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
    _members->_testCheckBox->SetBackgroundColors(_chbgd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testCheckBox->SetBackgroundColors(_chbgc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testCheckBox->SetBackgroundColors(_chbgh, RetroFuturaGUI::ColorState::Hover);
    _members->_testCheckBox->SetBorderColors(_chboe, RetroFuturaGUI::ColorState::Enabled);
    _members->_testCheckBox->SetBorderColors(_chbod, RetroFuturaGUI::ColorState::Disabled);
    _members->_testCheckBox->SetBorderColors(_chboc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testCheckBox->SetBorderColors(testv, RetroFuturaGUI::ColorState::Hover);
    _members->_testCheckBox->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testCheckBox->SetBorderGradientRotationSpeed(5.0f);
    _members->_testCheckBox->SetBorderWidth(2.0f);
    _members->_testCheckBox->SetCornerRadii(glm::vec4(10.0f));
    _members->_testCheckBox->SetInnerPadding(5.0f);

//RadioButton
    _members->_testRadioButton = std::make_unique<RetroFuturaGUI::RadioButton>("TestRadioButton", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window, nullptr);
    _members->_testRadioButton->SetSize({35.0f, 35.0f, 0.05f});
    _members->_testRadioButton->SetIndicatorColors(_chce, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton->SetIndicatorColors(_chcd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton->SetIndicatorColors(_chcc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton->SetIndicatorColors(_chch, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton->SetBackgroundColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton->SetBackgroundColors(_chbgd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton->SetBackgroundColors(_chbgc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton->SetBackgroundColors(_chbgh, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton->SetBorderColors(_chboe, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton->SetBorderColors(_chbod, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton->SetBorderColors(_chboc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton->SetBorderColors(testv, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testRadioButton->SetBorderGradientRotationSpeed(5.0f);
    _members->_testRadioButton->SetBorderWidth(2.0f);
    _members->_testRadioButton->SetCornerRadii(glm::vec4(17.0f));
    _members->_testRadioButton->SetIndicatorPadding(3.0f);

    _members->_testRadioButton2 = std::make_unique<RetroFuturaGUI::RadioButton>("TestRadioButton2", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window, nullptr);
    _members->_testRadioButton2->SetSize({35.0f, 35.0f, 0.05f});
    _members->_testRadioButton2->SetIndicatorColors(_chce, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton2->SetIndicatorColors(_chcd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton2->SetIndicatorColors(_chcc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton2->SetIndicatorColors(_chch, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton2->SetBackgroundColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton2->SetBackgroundColors(_chbgd, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton2->SetBackgroundColors(_chbgc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton2->SetBackgroundColors(_chbgh, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton2->SetBorderColors(_chboe, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButton2->SetBorderColors(_chbod, RetroFuturaGUI::ColorState::Disabled);
    _members->_testRadioButton2->SetBorderColors(_chboc, RetroFuturaGUI::ColorState::Clicked);
    _members->_testRadioButton2->SetBorderColors(testv, RetroFuturaGUI::ColorState::Hover);
    _members->_testRadioButton2->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testRadioButton2->SetBorderGradientRotationSpeed(5.0f);
    _members->_testRadioButton2->SetBorderWidth(2.0f);
    _members->_testRadioButton2->SetCornerRadii(glm::vec4(17.0f));
    _members->_testRadioButton2->SetIndicatorPadding(3.0f);

//RadioButtonGroup
    _members->_testRadioButtonGroup = std::make_unique<RetroFuturaGUI::RadioButtonGroup>("TextRadioButtonGroup", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testRadioButtonGroup->SetSize({200.0f, 200.0f, 0.05f});
    _members->_testRadioButtonGroup->SetPosition(glm::vec3(100.0f, 100.0f, 0.0f));
    _members->_testRadioButton->SetParentGroup(&*_members->_testRadioButtonGroup);
    _members->_testRadioButton2->SetParentGroup(&*_members->_testRadioButtonGroup);
    _members->_testRadioButtonGroup->SetGridContentAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testRadioButtonGroup->SetGridContentPadding(5.0f);
    
    //std::vector<RetroFuturaGUI::BorderGap> borderGaps;
    std::vector<RetroFuturaGUI::BorderGap> gapdef {{ 
        .edge = RetroFuturaGUI::BorderEdge::Left,
        .offset = 20.0f,
        .length = 160.0f,
        .anchorFarCorner = false,
        .repeat = 4
    }/*,
{ 
        .edge = RetroFuturaGUI::BorderEdge::Right,
        .offset = 20.0f,
        .length = 60.0f,
        .anchorFarCorner = false,
        .repeat = 4
    },
{ 
        .edge = RetroFuturaGUI::BorderEdge::Bottom,
        .offset = 20.0f,
        .length = 60.0f,
        .anchorFarCorner = false,
        .repeat = 4
    },
{ 
        .edge = RetroFuturaGUI::BorderEdge::Left,
        .offset = 20.0f,
        .length = 60.0f,
        .anchorFarCorner = false,
        .repeat = 4
    }*/};
    _members->_testRadioButtonGroup->SetBorderWidth(10.0f);
    _members->_testRadioButtonGroup->SetBorderColors(testv, RetroFuturaGUI::ColorState::Enabled);
    _members->_testRadioButtonGroup->SetBorderGaps(gapdef);
    _members->_testRadioButtonGroup->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testRadioButtonGroup->SetBorderGradientRotationSpeed(2.5f);
    _members->_testRadioButtonGroup->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testRadioButtonGroup->SetTextPadding(5.0f);
    _members->_testRadioButtonGroup->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman,PlatformBridge::Fonts::Weight::Normal);
    _members->_testRadioButtonGroup->SetText("bababooey", false);
    std::vector<f32> _rowDef { 0.5f, 0.5f };
    std::vector<f32> _colDef { 0.5f, 0.5f };
    _members->_testRadioButtonGroup->SetAxisDefinitions(_rowDef, _colDef);
    _members->_testRadioButtonGroup->RegisterRadioButton(&*_members->_testRadioButton, &*_members->_testRadioButtonText, glm::i64vec2(0,0));
    _members->_testRadioButtonGroup->RegisterRadioButton(&*_members->_testRadioButton2, &*_members->_testRadioButtonText2, glm::i64vec2(1,0));

//SLider
    _members->_testSlider = std::make_unique<RetroFuturaGUI::Slider>("TestSlider", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    //On-screen footprint, not the track's own axes: 20 wide by 350 tall, since this one is Vertical below
    _members->_testSlider->SetSize({20.0f, 350.0f, 0.05f});
    _members->_testSlider->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testSlider->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_testSlider->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testSlider->SetBorderWidth(2.0f);
    _members->_testSlider->SetIndicatorBackgroundColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
    _members->_testSlider->SetIndicatorBorderColors(_chboe, RetroFuturaGUI::ColorState::Enabled);
    _members->_testSlider->SetIndicatorSize(glm::vec2(20.0f, 100.0f), RetroFuturaGUI::IRangedValue::ElementSizing::Percent);
    // Recycled as the table's vertical scrollbar, so its range is set from the table's scroll
    // extent further down - the table doesn't exist yet at this point.
    //_members->_testSlider->SetMinValue<u32>(0);
    //_members->_testSlider->SetMaxValue<u32>(100);
    //_members->_testSlider->SetValue<u32>(50);
    //_members->_testSlider->SetStepSize<u32>(5);
    _members->_testSlider->SetOrientation(RetroFuturaGUI::IRangedValue::Orientation::Vertical);

//ProgressBar
    _members->_testProgressBar = std::make_unique<RetroFuturaGUI::ProgressBar>("TestSlider", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testProgressBar->SetSize({20.0f, 350.0f, 0.05f});
    _members->_testProgressBar->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testProgressBar->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_testProgressBar->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testProgressBar->SetBorderWidth(2.0f);
    _members->_testProgressBar->SetGraphColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
    _members->_testProgressBar->SetGraphWidth(20.0f);
    _members->_testProgressBar->SetMinValue<u32>(0);
    _members->_testProgressBar->SetMaxValue<u32>(100);
    _members->_testProgressBar->SetValue<u32>(50);
    _members->_testProgressBar->SetGraphMode(RetroFuturaGUI::IRangedValue::GraphMode::Wave);
    _members->_testProgressBar->SetIndicatorType(RetroFuturaGUI::IRangedValue::IndicatorType::Stroke);
    _members->_testProgressBar->EnableIndicator(true);
    _members->_testProgressBar->SetIndicatorSize(glm::vec2(8.0f, 18.0f), RetroFuturaGUI::IRangedValue::ElementSizing::Pixels);
    _members->_testProgressBar->SetIndicatorBackgroundColors(testv, RetroFuturaGUI::ColorState::Enabled);
    _members->_testProgressBar->SetIndicatorCornerRadii(glm::vec4(5.0f));
    _members->_testProgressBar->SetOrientation(RetroFuturaGUI::IRangedValue::Orientation::Vertical);

    RetroFuturaGUI::AxisDefinition stepperAxis
    {
        ._RowDefinition    = { 0.15f, 0.7f, 0.15f },
        ._ColumnDefinition = { 1.0f },
        ._LayerDefinition  = { 1.0f }
    };

    _members->_testStepper = std::make_unique<RetroFuturaGUI::Prefab>("TestStepper", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window, stepperAxis);

    RetroFuturaGUI::Button* _increase { _members->_testStepper->AttachWidget<RetroFuturaGUI::Button>("Increase", { ._Row = 0 }) };
    RetroFuturaGUI::Slider* _stepperSlider { _members->_testStepper->AttachWidget<RetroFuturaGUI::Slider>("Slider", { ._Row = 1 }) };
    RetroFuturaGUI::Button* _decrease { _members->_testStepper->AttachWidget<RetroFuturaGUI::Button>("Decrease", { ._Row = 2 }) };

    if(_increase != nullptr && _stepperSlider != nullptr && _decrease != nullptr)
    {
        for(RetroFuturaGUI::Button* _stepButton : { _increase, _decrease })
        {
            _stepButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
            _stepButton->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorState::Hover);
            _stepButton->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorState::Clicked);
            _stepButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
            _stepButton->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
            _stepButton->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
            _stepButton->SetBorderWidth(2.0f);
        }

        _stepperSlider->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        _stepperSlider->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
        _stepperSlider->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
        _stepperSlider->SetBorderWidth(2.0f);
        _stepperSlider->SetIndicatorBackgroundColors(_chbge, RetroFuturaGUI::ColorState::Enabled);
        _stepperSlider->SetIndicatorBorderColors(_chboe, RetroFuturaGUI::ColorState::Enabled);
        _stepperSlider->EnableIndicator(true);
        _stepperSlider->SetIndicatorSize(glm::vec2(15.0f, 100.0f), RetroFuturaGUI::IRangedValue::ElementSizing::Percent);

        //Min/max before the value: SetValue is what fixes the value's type, the bounds only compare against it
        _stepperSlider->SetMinValue<f32>(0.0f);
        _stepperSlider->SetMaxValue<f32>(100.0f);
        _stepperSlider->SetValue<f32>(0.0f);
        _stepperSlider->SetStepSize<f32>(10.0f);
        _stepperSlider->SetOrientation(RetroFuturaGUI::IRangedValue::Orientation::Vertical);

        //The prefab owns both the buttons and the slider, so the captured pointer cannot outlive the callback
        _increase->Connect_OnClick([_stepperSlider]() { _stepperSlider->StepValue(false); }, false);
        _decrease->Connect_OnClick([_stepperSlider]() { _stepperSlider->StepValue(true); }, false);
    }

//Table
    std::vector<glm::vec4> textColors {{1.0f, 1.0f, 1.0f, 1.0f}};
    std::vector<glm::vec4> tableBGcolors {{0.2f, 0.2f, 0.2f, 1.0f}};
    std::vector<glm::vec4> tableBorderColors {{0.5f, 0.5f, 0.5f, 1.0f}};
    std::vector<glm::vec4> textColors1 {{1.0f, 0.75f, 0.75f, 1.0f}};
    std::vector<glm::vec4> tableBGcolors1 {{0.35f, 0.35f, 0.35f, 1.0f}};
    std::vector<glm::vec4> tableBorderColors1 {{0.2f, 0.2f, 0.2f, 1.0f}};
    _members->_testTable = std::make_unique<RetroFuturaGUI::Table>("TestTable", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testTable->SetSize({400.0f, 200.0f, 0.05f});
    _members->_testTable->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    _members->_testTable->SetBorderWidth(2.0f);
    _members->_testTable->SetBorderColors(testv, RetroFuturaGUI::ColorState::Enabled);
    _members->_testTable->SetBorderFillType(RetroFuturaGUI::FillType::HUESTAR_GRADIENT);
    _members->_testTable->SetBorderGradientRotationSpeed(5.0f);
    //_members->_testTable->SetGridContentAlignment(RetroFuturaGUI::TextAlignment::Left);
    //_members->_testTable->SetGridContentPadding(5.0f);
    _members->_testTable->SetTrackBackgroundColors(tableBGcolors, RetroFuturaGUI::ColorState::Enabled, 0);
    _members->_testTable->SetTrackBorderColors(tableBorderColors, RetroFuturaGUI::ColorState::Enabled, 0);
    _members->_testTable->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman,PlatformBridge::Fonts::Weight::Normal);
    _members->_testTable->SetTextColors(textColors, RetroFuturaGUI::ColorState::Enabled, 0);
    _members->_testTable->SetTextAlignment(RetroFuturaGUI::TextAlignment::Left);
    _members->_testTable->SetTextPadding(5.0f);
    // Star rows always divide the table's own height, so the content could never outgrow the
    // viewport and there was nothing to scroll to.
    //std::vector<f32> _rowDefTable { 0.2f, 0.2f, 0.2f, 0.2f, 0.2f };
    //std::vector<f32> _colDefTable { 0.5f, 0.5f };
    // Fixed rows are sized in pixels regardless of the table: 5 x 60px = 300px of content in a
    // 200px tall table, leaving 100px to scroll through. Columns stay Star so they still fill
    // the width and no horizontal scrolling is needed.
    std::vector<RetroFuturaGUI::Table::TrackDefinition> _rowDefTable
    {
        { RetroFuturaGUI::Table::TrackSizing::Fixed, 60.0f },
        { RetroFuturaGUI::Table::TrackSizing::Fixed, 60.0f },
        { RetroFuturaGUI::Table::TrackSizing::Fixed, 60.0f },
        { RetroFuturaGUI::Table::TrackSizing::Fixed, 60.0f },
        { RetroFuturaGUI::Table::TrackSizing::Fixed, 60.0f }
    };
    std::vector<RetroFuturaGUI::Table::TrackDefinition> _colDefTable
    {
        { RetroFuturaGUI::Table::TrackSizing::Star, 0.5f },
        { RetroFuturaGUI::Table::TrackSizing::Star, 0.5f }
    };
    _members->_testTable->SetInnerBorderWidth(2.0f);
    _members->_testTable->SetTrackDefinitions(_rowDefTable, _colDefTable);
    _members->_testTable->SetValue(true, { ._Row = 0, ._Column = 0 }, false);
    _members->_testTable->SetTableWidget(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), { ._Row = 0, ._Column = 1 }, false);
    _members->_testTable->SetValue(false, { ._Row = 1, ._Column = 0 }, false);
    _members->_testTable->SetTableWidget(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), { ._Row = 1, ._Column = 1 }, false);
    _members->_testTable->SetValue(true, { ._Row = 2, ._Column = 0 }, false);
    _members->_testTable->SetTableWidget(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), { ._Row = 2, ._Column = 1 }, false);
    _members->_testTable->SetValue(true, { ._Row = 3, ._Column = 0 }, false);
    _members->_testTable->SetTableWidget(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), { ._Row = 3, ._Column = 1 }, false);
    _members->_testTable->SetValue(false, { ._Row = 4, ._Column = 0 }, false);
    _members->_testTable->SetTableWidget(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), { ._Row = 4, ._Column = 1 }, false);
    _members->_testTable->SetTrackAlternatingColorCount(2);
    _members->_testTable->SetTrackBackgroundColors(tableBGcolors1, RetroFuturaGUI::ColorState::Enabled, 1);
    _members->_testTable->SetTrackBorderColors(tableBorderColors1, RetroFuturaGUI::ColorState::Enabled, 1);
    _members->_testTable->SetTextColors(textColors1, RetroFuturaGUI::ColorState::Enabled, 1);
    _members->_testTable->SetTableOrientation(RetroFuturaGUI::Table::TableOrientation::Row);

//Table scrollbar (the recycled slider). The table owns the scroll state and just exposes it, so
//the slider only has to mirror the scrollable pixel range and push its value back in.
    _members->_testSlider->SetMinValue<f32>(0.0f);
    _members->_testSlider->SetMaxValue<f32>(_members->_testTable->GetMaxScroll().y);
    _members->_testSlider->SetStepSize<f32>(20.0f);
    _members->_testSlider->SetValue<f32>(0.0f); // sets the value type too, so it must come after the range

//The stepper prefab is what actually drives the scroll, so its slider carries the same range. Set here and
//not where the prefab is composed, because the table does not exist yet at that point.
    if(RetroFuturaGUI::Slider* _scrollSlider { _members->_testStepper->GetChildWidget<RetroFuturaGUI::Slider>("Slider") })
    {
        //Scroll offset 0 is the top of the content, so the track runs the opposite way to a normal slider
        _scrollSlider->SetTrackDirection(RetroFuturaGUI::IRangedValue::TrackDirection::Inverted);
        _scrollSlider->SetMinValue<f32>(0.0f);
        _scrollSlider->SetMaxValue<f32>(_members->_testTable->GetMaxScroll().y);
        _scrollSlider->SetStepSize<f32>(20.0f);
        _scrollSlider->SetValue<f32>(0.0f); // unscrolled, which Inverted puts at the top of the track
    }
    _members->_testTable->SetHeaderFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    _members->_testTable->SetHeaderTextColors(textColors, RetroFuturaGUI::ColorState::Enabled);
    _members->_testTable->SetHeaderBackgroundColors(tableBGcolors, RetroFuturaGUI::ColorState::Enabled);
    _members->_testTable->SetHeaderOuterBorderColors(tableBorderColors, RetroFuturaGUI::ColorState::Enabled);
    _members->_testTable->SetHorizontalHeaderSize(60.0f);
    _members->_testTable->ShowHorizontalHeader(true);
    _members->_testTable->SetHorizontalHeaderText("Column 0", 0);
    _members->_testTable->SetHorizontalHeaderText("Column 1", 1   );
    _members->_testTable->SetCheckBoxBackgroundColors(tableBGcolors, RetroFuturaGUI::ColorState::Enabled);

//ComboBox
    _members->_testComboBox = std::make_unique<RetroFuturaGUI::ComboBox>("TestComboBox", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testComboBox->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman,PlatformBridge::Fonts::Weight::Normal);
    _members->_testComboBox->AddItem("Item 0");
    _members->_testComboBox->AddItem("Item 1");
    _members->_testComboBox->AddItem("Item 2");
    _members->_testComboBox->AddItem("Item 3");
    _members->_testComboBox->AddItem("Item 4");
    _members->_testComboBox->AddItem("Item 5");
    _members->_testComboBox->AddItem("Item 6");
    _members->_testComboBox->AddItem("Item 7");
    _members->_testComboBox->AddItem("Item 8");
    _members->_testComboBox->AddItem("Item 9");
    _members->_testComboBox->SetSize(glm::vec3(240.0f, 60.0f, 0.01f));
    _members->_testComboBox->SetBackgroundColor(RetroFuturaGUI::ResourceManager::_Eigengrau, RetroFuturaGUI::ColorState::Enabled);

//ExtendedComboBox
    _members->_testExtendedComboBox = std::make_unique<RetroFuturaGUI::ExtendedComboBox>("TestExtendedComboBox", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testExtendedComboBox->SetFontFamily("Arial", 25.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    _members->_testExtendedComboBox->SetSize(glm::vec3(240.0f, 60.0f, 0.01f));
    _members->_testExtendedComboBox->SetBackgroundColor(RetroFuturaGUI::ResourceManager::_Eigengrau, RetroFuturaGUI::ColorState::Enabled);
    //the rows are whole widgets, so the closed box shows this text rather than the selected row
    _members->_testExtendedComboBox->SetPreviewText("Pick an item");

    //AddItem takes ownership and hands the item back, so each row can be configured after the font has been applied to it
    RetroFuturaGUI::Button* extendedComboBoxButton
    {
        _members->_testExtendedComboBox->AddItem(std::make_unique<RetroFuturaGUI::Button>("TestExtendedComboBoxButton", static_cast<RetroFuturaGUI::Projection*>(&projection), &*_members->_testExtendedComboBox, RetroFuturaGUI::WidgetTypeID::ExtendedComboBox, window))
    };
    extendedComboBoxButton->SetText("Button Item", false);
    extendedComboBoxButton->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.9f, 1.0f), RetroFuturaGUI::ColorState::Enabled);

    RetroFuturaGUI::Label* extendedComboBoxLabel
    {
        _members->_testExtendedComboBox->AddItem(std::make_unique<RetroFuturaGUI::Label>("TestExtendedComboBoxLabel", static_cast<RetroFuturaGUI::Projection*>(&projection), &*_members->_testExtendedComboBox, RetroFuturaGUI::WidgetTypeID::ExtendedComboBox, window))
    };
    extendedComboBoxLabel->SetText("Label Item", false);

    //the combo box becomes a row of the extended one, so its ownership moves here and it is no longer attached to the lasagna itself
    _members->_testExtendedComboBox->AddItem(std::move(_members->_testComboBox));
    //the combo box becomes a row of the extended one, so its ownership moves here and it is no longer attached to the lasagna itself
    _members->_testExtendedComboBox->SetDropDownPosition(RetroFuturaGUI::IDropDown::DropDownPosition::Right);

    _members->_testSeparatorLine = std::make_unique<RetroFuturaGUI::SeparatorLine>("Test Separator Lien", static_cast<RetroFuturaGUI::Projection*>(&projection), _rootLasagna, RetroFuturaGUI::WidgetTypeID::Lasagna, window);
    _members->_testSeparatorLine->SetSize(glm::vec3(200.0f, 5.0f, 0.01f));
    _members->_testSeparatorLine->SetBackgroundColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testSeparatorLine->SetBackgroundColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), RetroFuturaGUI::ColorState::Disabled);
    _members->_testSeparatorLine->SetEnabled(true, false);
    _members->_testSeparatorLine->SetBackgroundFillType(RetroFuturaGUI::FillType::SOLID);
    _members->_testSeparatorLine->SetFontFamily("Arial", 15.0f, PlatformBridge::Fonts::Slant::Roman, PlatformBridge::Fonts::Weight::Normal);
    _members->_testSeparatorLine->SetTextPadding(8.0f);
    _members->_testSeparatorLine->SetText("Section", false);
    _members->_testSeparatorLine->ShowText(true);

//Garnish lasagna
    _rootLasagna->AttachWidget(1, 1, 0, &*_members->_testLabel, RetroFuturaGUI::SizingMode::FIXED, 1, 2);
    _rootLasagna->AttachWidget(0, 0, 0, &*_members->_testTextBox, RetroFuturaGUI::SizingMode::FIXED, 1, 2); //swapped with the combo box, which needs a cell drawn later
    _rootLasagna->AttachWidget(2, 1, 0, &*_members->_testButton, RetroFuturaGUI::SizingMode::FIXED);
    //_rootLasagna->AttachWidget(0, 2, 0, &*_members->_testImage, RetroFuturaGUI::SizingMode::FIXED);
    _rootLasagna->AttachWidget(1, 1, 1, &*_members->_testSvgImage, RetroFuturaGUI::SizingMode::FILL_XY, 3, 2);
    //_rootLasagna->AttachWidget(3, 1, 0, &*_members->_testModel, RetroFuturaGUI::SizingMode::FIXED);
    //_rootLasagna->AttachWidget(3, 2, 0, &*_members->_testRadioButton, RetroFuturaGUI::SizingMode::FIXED);
    //_rootLasagna->AttachWidget(3, 2, 0, &*_members->_testRadioButtonGroup, RetroFuturaGUI::SizingMode::FILL_XY);
    //_rootLasagna->AttachWidget(3, 2, 0, &*_members->_testCheckBox, RetroFuturaGUI::SizingMode::FIXED);
    //FILL_Y, not FILL_X: for a Vertical slider the cell should drive its length, which now runs down the screen
    //_rootLasagna->AttachWidget(3, 0, 0, &*_members->_testSlider, RetroFuturaGUI::SizingMode::FILL_Y, 2, 1);
    //_rootLasagna->AttachWidget(3, 2, 0, &*_members->_testProgressBar, RetroFuturaGUI::SizingMode::FILL_X, 2, 1);
    _rootLasagna->AttachWidget(3, 1, 0, &*_members->_testTable, RetroFuturaGUI::SizingMode::FIXED, 2, 2);
    _rootLasagna->AttachWidget(3, 3, 0, &*_members->_testStepper, RetroFuturaGUI::SizingMode::FILL, 2, 1);
    _rootLasagna->AttachWidget(2, 0, 0, &*_members->_testSeparatorLine, RetroFuturaGUI::SizingMode::FIXED, 1, 1);

    //the combo box is a row of the extended one now, so the extended one takes the cell: row 2 so the open lists draw after the SvgImage on layer 1
    _rootLasagna->AttachWidget(2, 2, 0, &*_members->_testExtendedComboBox, RetroFuturaGUI::SizingMode::FIXED);



#ifdef DYNLIB_MODE
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testButton->GetName(), &*_members->_testButton);
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testLabel->GetName(), &*_members->_testLabel);
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testTextBox->GetName(), &*_members->_testTextBox);
#else
    _members->_testButton->Connect_OnClick([this]() { on_testButton_clicked(); }, false);
    _members->_testTextBox->Connect_OnTextChange([this]() { on_testTextBox_textChange(); }, false);
    _members->_testTextBox->Connect_OnEnterPressed([this]() { on_testTextBox_enterPressed(); }, false);
    _members->_testTextBox->Connect_OnEnterReleased([this]() { on_testTextBox_enterReleased(); }, false);
    _members->_testTextBox->Connect_OnCopy([this]() { on_testTextBox_copy(); }, false);
    _members->_testTextBox->Connect_OnPaste([this]() { on_testTextBox_paste(); }, false);
    //_members->_testSlider->Connect_OnValueChanged([this]() {on_testSlider_valueChanged(); }, false);
    // Scrollbar -> table. Nothing pushes back the other way yet, so there's no feedback loop to guard.
    if(RetroFuturaGUI::Slider* _scrollSlider { _members->_testStepper->GetChildWidget<RetroFuturaGUI::Slider>("Slider") })
    {
        //No inversion here any more - the slider's own TrackDirection handles it, so the value maps straight across
        _scrollSlider->Connect_OnValueChanged([this, _scrollSlider]()
            { _members->_testTable->SetVerticalScrollPosition(_scrollSlider->GetValue<f32>()); }, false);
    }
    _members->_testTable->Connect_OnTextChange([this]()-> void { on_testTableTextChange(); }, false);
#endif

    //_members->_testButton->SetRotation(glm::vec3(0.0f, 0.0f, 45.0f));
}
