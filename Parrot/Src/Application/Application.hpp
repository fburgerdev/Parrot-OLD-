#pragma once
#include "Window/Window.hpp"

namespace Parrot
{
	class Application
	{
	public:
		static Window* CreateMainWindow();

		static Window& MainWindow(); 
	};
}