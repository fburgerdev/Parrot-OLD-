#pragma once
#include <string>
#include "Window/Window.hpp"
#include "Utils/Stopwatch.hpp"

namespace Parrot
{
	namespace Application
	{		
		Window& GetWindow(const std::string& tag);
		Window& GetBoundWindow();
		Window& MainWindow();
		bool ContainsWindow(const std::string& tag);

		Utils::Timestep AbsTime();
	}
}