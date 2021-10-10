#pragma once
#include "Input/Event.hpp"

namespace Parrot
{
	// Virtual class for client application
	class Application
	{
	public:
		virtual void OnCreate() = 0;

		virtual void OnEvent(const Input::Event& e) = 0;
		virtual void OnUpdate() = 0;

		virtual void OnTerminate() = 0;
		static void Terminate();
		static void ThrowError();
	};
	// Returns pointer to client application
	// Needs to be defined by client!
	Application* CreateApplication();
}