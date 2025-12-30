#include <config.hpp>
#include <print>
#include "Window.hpp"
#include <chrono>
#include <thread>
#include "RetroFuturaGuiInit.hpp"
#include "MainWindow.hpp"

#ifndef DYNLIB_MODE

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __attribute__((visibility("default")))
#endif

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