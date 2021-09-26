#include "Parrot.h"

class Sandbox : public Parrot::Application
{
	virtual void OnCreate() override
	{
		Parrot::Window::Config config;
		Parrot::Window::Create("Sandbox", Parrot::Vector::Vec2u(1080, 720));
		Parrot::Window::VSync(true);
		Parrot::Window::ShowFrames(true);
	}

	virtual void OnEvent(const Parrot::Window::Event& e) override
	{
		//e.Log();
		if (e.GetType() == Parrot::Window::Event::Type::WindowCloseRequestEvent)
			Terminate();
	}

	virtual void OnUpdate() override
	{	
		Parrot::Log::StartScope("Keyboard Presses");
		if (Parrot::Window::Keyboard::GetState(Parrot::Window::Keyboard::Key::PT_KEY_SPACE) != Parrot::Window::Keyboard::KeyState::Released)
			Parrot::Log::LogInfo("Space Pressed!");
		Parrot::Log::EndScope();

		Parrot::Window::Display();
	}
	
	virtual void OnTerminate() override
	{
		Parrot::Window::Terminate();
	}
};

Parrot::Application* Parrot::CreateApplication()
{
	return new Sandbox();
}