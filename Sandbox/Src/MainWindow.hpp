#pragma once
#include "Parrot.hpp"

class MainWindow: public Parrot::Window
{
public:
	using Window::Window;
protected:
	virtual void OnCreate() override
	{
		Parrot::Log::LogInfo("Window OnCreate!");
	}
};
