#include "Ptpch.hpp"
#include "Application.hpp"
#include "Debug/InternalLog.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	// static
	static Window* s_MainWindow = nullptr;
	static std::unordered_map<std::string, Window*> s_Windows;
	static std::unordered_map<std::string, Scene*> s_Scenes;
	static Utils::Stopwatch s_ApplicationTime;

	static void Init()
	{
		Utils::Filepath::SetRoot("../Parrot/");
		InternalLog::LogInfo("Parrot initialized!");
	}
	static void Terminate()
	{
		InternalLog::LogInfo("Parrot terminated!");
	}

	// application member
	Window& Application::GetWindow(const std::string& tag)
	{
		InternalLog::LogAssert(s_Windows.find(tag) != s_Windows.end(), "Window \"%\" doesn't exist!", tag);
		return *s_Windows[tag];
	}
	Scene& Application::GetScene(const std::string& tag)
	{
		InternalLog::LogAssert(s_Scenes.find(tag) != s_Scenes.end(), "Scene \"%\" doesn't exist!", tag);
		return *s_Scenes[tag];
	}
	Utils::Timestep Application::AbsTime()
	{
		return s_ApplicationTime.Timing();
	}

	// hidden from client
	void HIDDEN_ApplicationAddWindow(const std::string& tag, Window* window)
	{
		if (s_Windows.empty())
			s_MainWindow = window;
		s_Windows[tag] = window;
	}
	void HIDDEN_ApplicationRemoveWindow(const std::string& tag)
	{
		if (s_MainWindow == s_Windows[tag])
			s_MainWindow = nullptr;
		s_Windows.erase(tag);
	}
	void HIDDEN_ApplicationAddScene(const std::string& tag, Scene* scene)
	{
		s_Scenes[tag] = scene;
	}
	void HIDDEN_ApplicationRemoveScene(const std::string& tag)
	{
		s_Scenes.erase(tag);
	}
}

using namespace Parrot;
int main()
{
	s_ApplicationTime.Start();
	Init();
	InternalLog::StartScope("OnCreate");
	Application::OnCreate();
	InternalLog::EndScope();
	InternalLog::StartScope("Runtime");
	InternalLog::LogAssert(s_MainWindow, "\"Application_OnCreate()\" needs to create at least one Window!");
	while (s_MainWindow && !s_MainWindow->ShouldClose())
	{
		for (auto& window : s_Windows)
		{
			if (window.second->ShouldClose())
			{
				delete window.second;
				break;
			}
			else
				window.second->Update();
		}
	}	
	InternalLog::EndScope();
	if (s_MainWindow)
		delete s_MainWindow;
	Terminate();
}