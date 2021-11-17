#pragma once
#include <string>
#include "ClientInterface/Window.hpp"
#include "Utils/Stopwatch.hpp"

namespace Parrot
{
	namespace Application
	{		
		Window& GetWindow(const std::string& tag);
		Window& MainWindow();

		Utils::Timestep AbsTime();
	}
}