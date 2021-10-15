#include "Parrot.hpp"
#include "MainWindow.hpp"

Parrot::Window* Parrot::Application::CreateMainWindow()
{
	return new Window("Main Window", Parrot::Math::Vec2u(500, 500));
}