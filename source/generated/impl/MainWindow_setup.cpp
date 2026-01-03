#include "MainWindow.hpp"
#include "PlatformBridge.hpp"

#ifndef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

#endif

void TestProject::MainWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    bool frutiger = false;


    _members = std::make_unique<MainWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(_members->_name, windowTitle, width, height);


    GLFWwindow* window = _members->_window->GetGlfwWindow();
    RetroFuturaGUI::Projection& projection = *_members->_window->GetProjection(); 
    glm::vec2 resolution = projection.GetResolution();
    std::string fontPath = PlatformBridge::Fonts::GetFontsInformation().front().second;


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


    _members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Enabled, RetroFuturaGUI::WindowBar::ElementType::Title);
    _members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Enabled, RetroFuturaGUI::WindowBar::ElementType::Title);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.1f, 0.1f, 0.65f), RetroFuturaGUI::ColorSetState::Enabled, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.2f, 0.2f, 0.65f), RetroFuturaGUI::ColorSetState::Hover, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(1.0f, 0.3f, 0.3f, 0.75f), RetroFuturaGUI::ColorSetState::Clicked, RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.75f), RetroFuturaGUI::ColorSetState::Enabled, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.75f), RetroFuturaGUI::ColorSetState::Hover, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.85f), RetroFuturaGUI::ColorSetState::Clicked, RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 0.75f), RetroFuturaGUI::ColorSetState::Enabled, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.7f, 0.7f, 0.7f, 0.75f), RetroFuturaGUI::ColorSetState::Hover, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetElementBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 0.85f), RetroFuturaGUI::ColorSetState::Clicked, RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::CloseButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MaximizeButton);
	_members->_window->GetWindowBar().SetButtonCornerRadii(glm::vec4(10.0f), RetroFuturaGUI::WindowBar::ElementType::MinimizeButton);


    IdentityParams identityGrid = { "testGrid", this, WidgetTypeID::Grid2d, window };
	GeometryParams2D geometryGrid = { projection, glm::vec2(0.0f, 0.0f), resolution, 0.0f };
	RetroFuturaGUI::Grid2dAxisDefinition axisDefinition = 
	{
		{ 0.3f, 0.5f, 0.2f },
		{ 0.6f, 0.4f }
	};

	_members->_testGrid = std::make_unique<RetroFuturaGUI::Grid2d>(identityGrid, geometryGrid, axisDefinition);
std::string tempID = _members->_name +  "/testButton";
    IdentityParams identityB = { tempID, this, WidgetTypeID::Window, window };
	GeometryParams2D geometryB = { projection, glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 90.0f), 0.0f };
	RetroFuturaGUI::TextParams textParamsB = { "Test Button", fontPath, glm::vec4(1.0f), glm::vec2(30.0f), RetroFuturaGUI::TextAlignment::CENTER, 5.0f };
	RetroFuturaGUI::BorderParams borderParams = { glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), 5.0f };


	_members->_testButton = std::make_unique<RetroFuturaGUI::Button>(identityB, geometryB, textParamsB, 5.0f);


    if(frutiger)
    {
        
	_members->_testButton->SetCornerRadii(glm::vec4(45.0f));
	_members->_testButton->SetWindowBackgroundImageTextureID(_members->_window->GetBackgroundImageId());
	_members->_testButton->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Enabled);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Hover);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), RetroFuturaGUI::ColorSetState::Clicked);

    
    }
    else
    {

        std::vector<glm::vec4> testv = std::vector<glm::vec4>({{ 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} ,  { 0.980f, 0.851f, 0.875f, 1.0f }
            , { 0.965f, 0.761f, 0.965f, 1.0f }, { 0.024f, 0.478f, 0.965f, 1.0f},{ 0.024f, 0.478f, 0.965f, 1.0f} , { 0.718f, 0.976f, 0.992f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }, { 0.980f, 0.851f, 0.875f, 1.0f }});
        _members->_testButton->SetCornerRadii(glm::vec4(20.0f));
        _members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), RetroFuturaGUI::ColorSetState::Enabled);
        _members->_testButton->SetBackgroundColor(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), RetroFuturaGUI::ColorSetState::Hover);
        _members->_testButton->SetBackgroundColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), RetroFuturaGUI::ColorSetState::Clicked);

        _members->_testButton->SetBorderColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), RetroFuturaGUI::ColorSetState::Enabled);
        _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorSetState::Hover);
        _members->_testButton->SetBorderColors(testv, RetroFuturaGUI::ColorSetState::Clicked);

        _members->_testButton->SetBorderGradientAnimationSpeed(0.0f);
        _members->_testButton->SetBorderGradientRotationSpeed(0.1f);
    

    }
    
    _members->_testGrid->AttachWidget(1, 1, &*_members->_testButton, SizingMode::FIXED);

#ifndef DYNLIB_MODE
    RetroFuturaGUI::DynamicLibWidgetManager::AddWidget(_members->_testButton->GetName(), &*_members->_testButton);
#else
    _members->_testButton->Connect_OnClick([this]() { on_testButton_clicked(); }, false);
#endif

    //_members->_testButton->SetRotation(45.0f);

    _members->_window->SetGrid(&*_members->_testGrid);
}