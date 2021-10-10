#include "Parrot.hpp"

class Sandbox : public Parrot::Application
{
public:
	int a = 0;
	virtual void OnCreate() override
	{
		Parrot::Time::Framerate(60);
		Parrot::Window::ShowFrames(true);
	}

	virtual void OnEvent(const Parrot::Input::Event& e) override
	{
		if (e.type == Parrot::Input::Event::Type::WindowCloseRequestEvent)
			Terminate();
		if (e.type == Parrot::Input::Event::Type::KeyboardEvent)
			e.Log();
	}

	virtual void OnUpdate() override
	{
		Parrot::Log::LogInfo("Cursor = %", Parrot::Window::GetCursorPos());
		Parrot::Window::Display();
	}

	virtual void OnTerminate()
	{

	}
};

Parrot::Application* Parrot::CreateApplication()
{
	return new Sandbox();
}