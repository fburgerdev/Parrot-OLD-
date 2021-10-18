#pragma once
#include <string>
#include "ClientInterface/Window.hpp"
#include "Utils/Stopwatch.hpp"

namespace Parrot
{
	class Application
	{
	public:
		static void OnCreate();
	public:
		static Window& GetWindow(const std::string& tag);
		static Scene& GetScene(const std::string& tag);

		static Utils::Timestep AbsTime();
	};
}