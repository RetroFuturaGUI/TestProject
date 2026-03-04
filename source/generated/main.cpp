#include <config.hpp>
#include "IncludeHelper.hpp"
#include <print>
#include "Window.hpp"
#include <chrono>
#include <thread>
#include "RetroFuturaGuiInit.hpp"
#include "MainWindow.hpp"

#ifdef DYNLIB_MODE

#include "DynamicLibWidgetManager.hpp"

static std::unique_ptr<TestProject::MainWindow> mainWindowTest;

extern "C" EXPORT_API void SetWorkingDirectory(const char* dir)
{
    PlatformBridge::Paths::SetWorkingDir(dir);
}

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

extern "C" EXPORT_API void SetBackgroundGradientOffset(const char* id, f32 gradientOffset)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientOffset(id, gradientOffset);
}

extern "C" EXPORT_API void SetBackgroundGradientAnimationSpeed(const char* id, f32 animationSpeed)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientAnimationSpeed(id, animationSpeed);
}

extern "C" EXPORT_API void SetBackgroundGradientDegree(const char* id, f32 degree)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientDegree(id, degree);
}

extern "C" EXPORT_API void SetBackgroundGradientRotationSpeed(const char* id, f32 rotationSpeed)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBackgroundGradientRotationSpeed(id, rotationSpeed);
}

extern "C" EXPORT_API void SetWindowBackgroundImageTextureID(const char* id, u32 textureID)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetWindowBackgroundImageTextureID(id, textureID);
}

extern "C" EXPORT_API void SetBorderColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
	std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderColors(id, col, colorState);
}

extern "C" EXPORT_API void SetBorderGradientOffset(const char* id, f32 gradientOffset)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientOffset(id, gradientOffset);
}

extern "C" EXPORT_API void SetBorderGradientAnimationSpeed(const char* id, f32 animationSpeed)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientAnimationSpeed(id, animationSpeed);
}

extern "C" EXPORT_API void SetBorderGradientDegree(const char* id, f32 degree)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientDegree(id, degree);
}

extern "C" EXPORT_API void SetBorderGradientRotationSpeed(const char* id, f32 rotationSpeed)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetBorderGradientRotationSpeed(id, rotationSpeed);
}

extern "C" EXPORT_API void SetWindowBorderImageTextureID(const char* id, u32 textureID)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetWindowBorderImageTextureID(id, textureID);
}

extern "C" EXPORT_API void SetEnabled(const char* id, bool enabled)
{
	RetroFuturaGUI::DynamicLibWidgetManager::SetEnabled(id, enabled);
}

extern "C" EXPORT_API void SetTextColors(const char* id, f32* colors, u32 colorCount, RetroFuturaGUI::ColorState colorState)
{
	std::span<glm::vec4> col(reinterpret_cast<glm::vec4*>(colors), colorCount);
	RetroFuturaGUI::DynamicLibWidgetManager::SetTextColors(id, col, colorState);
}

#endif

i32 main()
{
	PlatformBridge::RefreshPlatformBridge();
	std::string exePath = PlatformBridge::Paths::GetExecutablePath();

#ifdef _WIN32
    exePath = exePath.substr(0, exePath.find_last_of(R"(\)"));
#else
    exePath = exePath.substr(0, exePath.find_last_of(R"(/)"));
#endif

	PlatformBridge::Paths::SetWorkingDir(exePath.c_str());

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