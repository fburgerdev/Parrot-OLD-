#pragma once
#include "Event.h"

int main();

namespace Parrot
{
	class Application
	{
	public:
		static void Terminate();


		virtual void OnCreate() = 0;
		virtual void OnEvent(const Window::Event& e) = 0;
		virtual void OnUpdate() = 0;
		virtual void OnTerminate() = 0;
	};

	Application* CreateApplication();
}
