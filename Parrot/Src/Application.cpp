#include "Application.h"
#include "Log.h"
#include "GLFW/glfw3.h"
#include "Window.h"

static bool s_Run = true;
static Parrot::Application* s_Application;

int main()
{
	s_Application = Parrot::CreateApplication();
	
	Parrot::Log::StartScope("OnCreate");
	s_Application->OnCreate();
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnUpdate");
	while (s_Run)
		s_Application->OnUpdate();
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnTerminate");
	s_Application->OnTerminate();
	Parrot::Log::EndScope();

	return 0;
}

void Parrot::Application::Terminate()
{
	s_Run = false;
}

void PushEvent(const Parrot::Window::Event& e)
{
	s_Application->OnEvent(e);
}