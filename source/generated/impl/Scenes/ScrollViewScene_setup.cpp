#include "ScrollViewScene.hpp"
#include "ScrollViewScene_p.hpp"
#include "Window.hpp"
#include "SceneLoader.hpp"
#include "IncludeHelper.hpp"
#include "PlatformBridge.hpp"
#include "Fonts.hpp"
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <vector>

#ifdef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

#endif

TestProject::ScrollViewScene::ScrollViewScene(RetroFuturaGUI::Window* parentWindow)
{
    _members = std::make_unique<ScrollViewScene_p>();
    setup(parentWindow);
}

TestProject::ScrollViewScene::~ScrollViewScene()
{
    //Unregister before the scene is freed, or the loader's registry and the window's draw order
    //are left holding a pointer to it.
    if(!_members)
        return;

    if(!_members->_scene)
        return;

    RetroFuturaGUI::SceneLoader::UnregisterScene(RetroFuturaGUI::SceneLoader::GetSceneID(_members->_scene->GetName()));
}

RetroFuturaGUI::Scene* TestProject::ScrollViewScene::GetScene() const
{
    if(!_members)
        return nullptr;

    return _members->_scene.get();
}

RetroFuturaGUI::Video* TestProject::ScrollViewScene::GetVideo() const
{
    if(!_members)
        return nullptr;

    return _members->_testVideo;
}

void TestProject::ScrollViewScene::setup(RetroFuturaGUI::Window* parentWindow)
{
    if(!parentWindow)
        return;

    RetroFuturaGUI::Projection* projection { parentWindow->GetProjection() };

    if(!projection)
        return;

//A scene with a ScrollView as its root instead of a Lasagna, so the whole scene scrolls. It is an overlay in a window of
//its own, so it spans whatever that window's menu bar leaves. The ScrollView stacks the video, the button, the histogram and the color picker top
//to bottom, in the order they are added, and owns all four.
    _members->_scene = RetroFuturaGUI::SceneLoader::CreateScene("ScrollViewScene", parentWindow);

    if(!_members->_scene)
        return;

    _members->_scrollView = _members->_scene->SetRootContainer<RetroFuturaGUI::ScrollView>(projection);

    if(!_members->_scrollView)
        return;

//Video
    //Added before the button so that it sits above it.
    _members->_testVideo = _members->_scrollView->AddWidget<RetroFuturaGUI::Video>("TestVideo");

    if(!_members->_testVideo)
        return;

    //Inside the ScrollView a widget keeps its own size, so the video needs one: 16:9 and narrower than the window.
    //The picture fits inside it, with black bars where the shapes differ.
    _members->_testVideo->SetSize(glm::vec3(480.0f, 270.0f, 0.01f));
    _members->_testVideo->SetFrequencyBandCount(50);

//Button
    _members->_testButton = _members->_scrollView->AddWidget<RetroFuturaGUI::Button>("TestButton");

    if(!_members->_testButton)
        return;

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

//Histogram
    _members->_testHistogram = _members->_scrollView->AddWidget<RetroFuturaGUI::Histogram>("TestHistogram");

    if(!_members->_testHistogram)
        return;

    _members->_testHistogram->SetData<f32>(_members->_testVideo->GetFrequencyBands(), false);
    //300 tall, so video, button and histogram (270 + 90 + 300 = 660) nearly fill the 680 px under the 40 px menu bar, before the color picker below adds its 250.
    //The ScrollView doesn't clip yet: the overflow below runs off the window.
    _members->_testHistogram->SetSize(glm::vec3(400.0f, 300.0f, 0.05f));
    _members->_testHistogram->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorState::Enabled);
    _members->_testHistogram->SetGraphColors(testv, RetroFuturaGUI::ColorState::Enabled);
    _members->_testHistogram->SetMinValue(0.0f);
    _members->_testHistogram->SetMaxValue(1.0f);
    _members->_testHistogram->EnableGraph(true);
    _members->_testHistogram->EnableIndicator(false);

//ColorPicker
    //Last in the ScrollView, so the stack is 270 + 90 + 300 + 250 = 910 px and leaves 230 px to scroll in the 680 px under the menu bar.
    //A vertical drag that starts on it scrolls the view, a click or a sideways drag picks.
    _members->_testColorPicker = _members->_scrollView->AddWidget<RetroFuturaGUI::ColorPicker>("TestColorPicker");

    if(!_members->_testColorPicker)
        return;

    _members->_testColorPicker->SetSize(glm::vec3(250.0f, 250.0f, 0.01f));
    std::vector<glm::vec4> colorPickerBorderColors { glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };
    _members->_testColorPicker->SetColorPickerFieldBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Enabled);
    _members->_testColorPicker->SetColorPickerFieldBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Hover);
    _members->_testColorPicker->SetColorPickerFieldBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Clicked);
    _members->_testColorPicker->SetColorPickerFieldBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Disabled);
    _members->_testColorPicker->SetColorPickerIndicatorBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Enabled);
    _members->_testColorPicker->SetColorPickerIndicatorBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Hover);
    _members->_testColorPicker->SetColorPickerIndicatorBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Clicked);
    _members->_testColorPicker->SetColorPickerIndicatorBorderColors(colorPickerBorderColors, RetroFuturaGUI::ColorState::Disabled);

#ifdef DYNLIB_MODE
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testButton->GetName(), _members->_testButton);
#else
    //On release rather than on press: a press that turns into a scroll, or slides off the button before it is let go, never plays the video
    _members->_testButton->Connect_OnRelease([this]() { on_testButton_clicked(); }, false);
#endif
}
