#pragma once
#include "Ptpch.hpp"
#include "ClientInterface/Window.hpp"
#include "Utils/Stopwatch.hpp"
#include "Scene/Scene.hpp"

namespace Parrot
{
	class Application
	{
	public:
		static Window& GetWindow(const std::string& tag);
		static Scene& GetScene(const std::string& tag);

		static Utils::Timestep AbsTime();
	};
}