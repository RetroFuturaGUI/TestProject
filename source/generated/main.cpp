#include <config.hpp>
#include <print>
#include <glad/glad.h>
#include <MainWindow.hpp>

int main()
{


	RetroFuturaGUI::MainWindow mainWindow("Test Window", 1280, 720);
	
	while (!mainWindow.WindowShouldClose())
	{
		mainWindow.Draw();
	}


	glfwTerminate();
	return 0;
}