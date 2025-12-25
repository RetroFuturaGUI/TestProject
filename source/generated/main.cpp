#include <config.hpp>
#include <print>
#include "Window.hpp"
#include <chrono>
#include <thread>
#include "RetroFuturaGuiInit.hpp"
#include "MainWindow.hpp"

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