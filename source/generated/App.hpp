#pragma once
#include "IncludeHelper.hpp"
#include "Window.hpp"

namespace RetroFuturaGUI
{
    class App
    {
    public:
        App()
        {
            setupOpenGL();
            //build();
        }

        ~App()
        {
            glfwTerminate();
        }

        bool Draw()
        {
            if(_mainWindow)
                _mainWindow->Draw();
        }

        bool AppShouldClose()
        {
            if(_mainWindow)
                return _mainWindow->WindowShouldClose();

            return true;
        }

    private:
        std::unique_ptr<Window> _mainWindow;
        std::unique_ptr<Grid2d> _mainWindowGrid;



        void build()
        {
            _mainWindow = std::make_unique<Window>("MainWindow", 1280, 720);
            
            IdentityParams identityTestGrid = { "testGrid", this, WidgetTypeID::Grid2d, _mainWindow->GetGlfwWindow() };
            GeometryParams2D geometryTestGrid = { *_mainWindow->GetProjection(), glm::vec2(0.0f, 0.0f), _mainWindow->GetProjection()->GetResolution(), 0.0f };
            Grid2dAxisDefinition axisDefinition = 
            {
                { 0.3f, 0.5f, 0.2f },
                { 0.6f, 0.4f }
            };

	        _mainWindowGrid = std::make_unique<Grid2d>(identityTestGrid, geometryTestGrid, axisDefinition);

            GeometryParams2D geometryBackgroundImage
            {
                *_mainWindow->GetProjection(),
                _mainWindow->GetProjection()->GetResolution() * 0.5f,
                _mainWindow->GetProjection()->GetResolution(),
                0.0f
            };

	        std::unique_ptr<Image2D> backgroundImage = std::make_unique<Image2D>(geometryBackgroundImage);


            IdentityParams identity = { "testLabel", this, WidgetTypeID::Window, _mainWindow->GetGlfwWindow() };
            GeometryParams2D geometry = { *_mainWindow->GetProjection(), glm::vec2(800.0f, 600.0f), glm::vec2(300.0f, 90.0f), 0.0f };
            std::string tempPath = PlatformBridge::Fonts::GetFontsInformation().front().second;
            TextParams textParams = { "Test Label", tempPath, glm::vec4(1.0f), glm::vec2(30.0f), TextAlignment::CENTER, 5.0f };

            IdentityParams identityB = { "testButton", this, WidgetTypeID::Window, _mainWindow->GetGlfwWindow() };
            GeometryParams2D geometryB = { *_mainWindow->GetProjection(), glm::vec2(0.0f, 0.0f), glm::vec2(300.0f, 90.0f), 0.0f };
            TextParams textParamsB = { "Test Button", tempPath, glm::vec4(1.0f), glm::vec2(30.0f), TextAlignment::CENTER, 5.0f };
            BorderParams borderParams = { glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), 5.0f };


            std::unique_ptr<Button> _button = std::make_unique<Button>(identityB, geometryB, textParamsB, borderParams);
            _button->SetCornerRadii(glm::vec4(45.0f));
            _button->SetWindowBackgroundImageTextureID(backgroundImage->GetTextureID());
            _button->SetBackgroundColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.65f), ColorSetState::Enabled);
            _button->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 1.0f, 0.65f), ColorSetState::Hover);
            _button->SetBackgroundColor(glm::vec4(0.2f, 0.2f, 1.0f, 0.75f), ColorSetState::Clicked);



            std::unique_ptr _label = std::make_unique<Label>(identity, geometry, textParams);
            

            auto buttonPressed = [](){ std::println("buttonPressed Slot"); };
            auto buttonReleased = [](){ std::println("buttonReleased Slot"); };
            auto whileHover = [](){ std::println("whileHover Slot"); };
            auto mouseEnter = [](){ std::println("mouseEnter Slot"); };
            auto mouseLeave = [](){ std::println("mouseLeave Slot"); };
            _button->Connect_OnClick(buttonPressed, true);
            _button->Connect_OnRelease(buttonReleased, true);
            //_button->Connect_WhileHover(whileHover, true);
            _button->Connect_OnMouseEnter(mouseEnter, true);
            _button->Connect_OnMouseLeave(mouseLeave, true);

            _mainWindowGrid->AttachWidget(1, 1, std::unique_ptr<IWidget>(std::move(_button)), SizingMode::FIXED);

        }

        void setupOpenGL()
        {
            if (!glfwInit())
            {
                std::println("glfw couldn't start");
                return;
            }
        }

        
    };
}