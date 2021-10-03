#pragma once
#include "Event.hpp"
#include "Vector.hpp"
int main();

namespace Parrot
{
	class Application
	{
	public:
		Application(const char* title, Parrot::Vector::Vec2u dim, const Parrot::Window::Config& = Parrot::Window::c_DefaultConfig);
		virtual ~Application();

		virtual void OnCreate() = 0;
		virtual void OnEvent(const Event& e) = 0;
		virtual void OnUpdate() = 0;
		virtual void OnTerminate() = 0;

		static bool IsOk();
		static void ThrowError();
		static void Terminate();
	};

	Application* CreateApplication();
}
