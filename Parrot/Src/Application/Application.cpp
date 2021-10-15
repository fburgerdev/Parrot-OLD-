#include "Ptpch.hpp"
#include "Application.hpp"
#include "Debug/Log.hpp"

namespace Parrot
{
	Window* s_MainWindow;

	void Init()
	{
		Log::LogInfo("Parrot initialized!");
	}
	void Terminate()
	{
		Log::LogInfo("Parrot terminated!");
	}
	Window& Application::MainWindow()
	{
		return *s_MainWindow;
	}
}

int main()
{
	Parrot::Init();
	Parrot::s_MainWindow = Parrot::Application::CreateMainWindow();
	Parrot::Window* w1 = new Parrot::Window("W1", Parrot::Math::Vec2u(100, 200));
	Parrot::Window* w2 = new Parrot::Window("W2", Parrot::Math::Vec2u(100, 300));
	while (!Parrot::s_MainWindow->ShouldClose())
	{
		Parrot::s_MainWindow->Update();
		w1->Update();
		w2->Update();
	}
	Parrot::Terminate();
}