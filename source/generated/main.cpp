#include <config.hpp>
#include "IncludeHelper.hpp"
#include <print>
#include "Window.hpp"
#include <chrono>
#include <thread>
#include "RetroFuturaGuiInit.hpp"
#include "MainWindow.hpp"

#ifndef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

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
	RetroFuturaGUI::DynamicLibWidgetManager::ConnectSlot(id, callback, action, async);
}

extern "C" EXPORT_API void DisonnectSlot(const char* id, RetroFuturaGUI::CallbackType callback, const i32 action)
{
	RetroFuturaGUI::DynamicLibWidgetManager::DisconnectSlot(id, callback, action);
}

extern "C" EXPORT_API void SetRotation(const char* id, f32 degree)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetRotation(id, degree);
}

extern "C" EXPORT_API void SetSize(const char* id, f32 width, f32 height)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetSize(id, width, height);
}

extern "C" EXPORT_API void SetBackgroundColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
	std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
	RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundColors(id, col, colorState);
}

extern "C" EXPORT_API void SetBorderColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
	std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderColors(id, col, colorState);
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