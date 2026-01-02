#include <config.hpp>
#include <print>
#include "Window.hpp"
#include <chrono>
#include <thread>
#include "RetroFuturaGuiInit.hpp"
#include "MainWindow.hpp"

#ifndef DYNLIB_MODE

#include "WidgetIdManager.hpp"

static std::unique_ptr<TestProject::MainWindow> mainWindowTest;

extern "C" EXPORT_API void InitRetroFuturaGUI()
{
	PlatformBridge::RefreshPlatformBridge();
	RetroFuturaGUI::GlfwInit();

	mainWindowTest = std::make_unique<TestProject::MainWindow>("RetroFuturaGUI Test", 1280, 720);
}

extern "C" EXPORT_API void Draw()
{
	while(!mainWindowTest->WindowShouldClose())
	{
		mainWindowTest->Draw();
	}

	RetroFuturaGUI::GlfwTerminate();
}

extern "C" EXPORT_API void ConnectSlot(const char* id, RetroFuturaGUI::CallbackType callback, const i32 action, const bool async)
{
	RetroFuturaGUI::WidgetIdManager::ConnectSlot(id, callback, action, async);
}

#else

i32 main()
{
	PlatformBridge::RefreshPlatformBridge();
	RetroFuturaGUI::GlfwInit();

	TestProject::MainWindow mainWindowTest("RetroFuturaGUI Test", 1280, 720);

	while(!mainWindowTest.WindowShouldClose())
	{
		mainWindowTest.Draw();
	}

	RetroFuturaGUI::GlfwTerminate();
	
	return 0;
}

#endif