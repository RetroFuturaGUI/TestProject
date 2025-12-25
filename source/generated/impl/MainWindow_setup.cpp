#include "MainWindow.hpp"
#include "PlatformBridge.hpp"

void TestProject::MainWindow::setup(std::string_view windowTitle, const i32 width, const i32 height)
{
    _members = std::make_unique<MainWindow_p>();
    _members->_window = std::make_unique<RetroFuturaGUI::Window>(windowTitle, width, height);


    GLFWwindow* window = _members->_window->GetGlfwWindow();
    RetroFuturaGUI::Projection& projection = *_members->_window->GetProjection(); 
    glm::vec2 resolution = projection.GetResolution();
    std::string fontPath = PlatformBridge::Fonts::GetFontsInformation().front().second;

    std::string path = PlatformBridge::Paths::GetExecutablePath();

#if defined(_WIN32) || defined(_WIN64)
    path = path.substr(0, path.find_last_of(R"(\)"));
    path.append(R"(\Resources\img\FrutigerAero.png)");
#else
    path = path.substr(0, path.find_last_of(R"(/)"));
    path.append("/ShaderSource/");
#endif

    _members->_window->SetBackgroundImage(path);

    IdentityParams identityGrid = { "testGrid", this, WidgetTypeID::Grid2d, window };
	GeometryParams2D geometryGrid = { projection, glm::vec2(0.0f, 0.0f), resolution, 0.0f };
	RetroFuturaGUI::Grid2dAxisDefinition axisDefinition = 
	{
		{ 0.3f, 0.5f, 0.2f },
		{ 0.6f, 0.4f }
	};

	_members->_testGrid = std::make_unique<RetroFuturaGUI::Grid2d>(identityGrid, geometryGrid, axisDefinition);

    IdentityParams identityB = { "testButton", this, WidgetTypeID::Window, window };
	GeometryParams2D geometryB = { projection, glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 90.0f), 0.0f };
	RetroFuturaGUI::TextParams textParamsB = { "Test Button", fontPath, glm::vec4(1.0f), glm::vec2(30.0f), RetroFuturaGUI::TextAlignment::CENTER, 5.0f };
	RetroFuturaGUI::BorderParams borderParams = { glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), 5.0f };


	_members->_testButton = std::make_unique<RetroFuturaGUI::Button>(identityB, geometryB, textParamsB, borderParams);
	_members->_testButton->SetCornerRadii(glm::vec4(45.0f));
	//_button->SetWindowBackgroundImageTextureID(_backgroundImage->GetTextureID());
	_members->_testButton->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Enabled);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), RetroFuturaGUI::ColorSetState::Hover);
	_members->_testButton->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), RetroFuturaGUI::ColorSetState::Clicked);

    _members->_testGrid->AttachWidget(1, 1, &*_members->_testButton, SizingMode::FIXED);
    _members->_testButton->Connect_OnClick([this]() { on_testButton_clicked(); }, false);

    _members->_window->SetGrid(&*_members->_testGrid);
}