#pragma once
#include "Window/Window.hpp"
#include "Utils/Stopwatch.hpp"

namespace Parrot
{
	namespace Application
	{		
		Window& GetWindow(const std::string& tag);
		Window& GetBoundWindow();
		Window& GetMainWindow();
		bool ContainsWindow(const std::string& tag);

		Utils::Timestep AbsTime();
	}
}