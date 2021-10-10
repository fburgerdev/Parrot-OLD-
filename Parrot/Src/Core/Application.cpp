#include "Ptpch.hpp"
#include "Application.hpp"
#include "Log.hpp"
#include "Time.hpp"
#include "HiddenFunctions.hpp"
#include "Window/WindowAPI.hpp"

// Statics
static Parrot::Application* s_Application;
static bool s_IsRunning = true;
static bool s_IsOk = true;

namespace Parrot
{
	void Application::Terminate()
	{
		s_IsRunning = false;
	}
	void Application::ThrowError()
	{
		s_IsRunning = false;
		s_IsOk = false;
	}

	void TriggerOnEvent(const Input::Event& e)
	{
		s_Application->OnEvent(e);
	}
}

static void InitParrot()
{
	Parrot::InitKeyStrings();
	s_Application = Parrot::CreateApplication();
	Parrot::Log::LogInfo("Application created successfully!");

	Parrot::WindowAPI::s_DefaultWindow = Parrot::WindowAPI::Create("hallo", Parrot::Math::Vec2u(1080, 720));
	Parrot::WindowAPI::SetContext(Parrot::WindowAPI::s_DefaultWindow);
}

int main()
{
	Parrot::StartGlobalStopwatch();
	InitParrot();

	Parrot::Log::StartScope("OnCreate");
	s_Application->OnCreate();
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnUpdate");
	while (s_IsRunning)
	{
		Parrot::ResolveUpdateStopwatch();
		s_Application->OnUpdate();
	}
	Parrot::Log::EndScope();

	Parrot::Log::StartScope("OnTerminate");
	s_Application->OnTerminate();
	Parrot::Log::EndScope();

	delete s_Application;
	Parrot::Log::LogInfo("Application terminated successfully after % seconds.", Parrot::Time::AbsTime().Seconds());

	std::cout << "\033[0m";
	return EXIT_SUCCESS;
}