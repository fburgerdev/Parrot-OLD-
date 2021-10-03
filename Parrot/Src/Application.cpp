#include "Pch.hpp"
#include "Application.hpp"
#include "Log.hpp"

namespace Parrot
{
	static Application* s_Application;
	
	void InitKeyStrings();
	void DisplayWindow();
	void PushEvent(const Parrot::Event& e)
	{
		s_Application->OnEvent(e);
	}
}

static void Pause()
{
	std::getchar();
}

static bool s_Run = true;
static bool s_IsOk = true;
int main()
{
	Parrot::InitKeyStrings();
	Parrot::s_Application = Parrot::CreateApplication();
	
	Parrot::Log::StartScope("OnCreate");
	Parrot::s_Application->OnCreate();
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnUpdate");
	while (s_Run)
	{
		Parrot::s_Application->OnUpdate();
		Parrot::DisplayWindow();
	}
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnTerminate");
	Parrot::s_Application->OnTerminate();
	Parrot::Log::EndScope();

	delete Parrot::s_Application;
	if (s_IsOk)
		Parrot::Log::LogInfo("Parrot terminated successfully! Press Enter to close console.");
	else
		Parrot::Log::LogError("Parrot terminated due to an fatal Error! Press Enter to close console.");
	Pause();
	return 0;
}

void Parrot::Application::Terminate()
{
	s_Run = false;
}

void Parrot::Application::ThrowError()
{
	s_Run = false;
	s_IsOk = false;
}

bool Parrot::Application::IsOk()
{
	return s_IsOk;
}