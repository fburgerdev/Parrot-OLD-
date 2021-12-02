#include "Ptpch.hpp"
#include "Application.hpp"
#include "Internal_Application.hpp"

#include "Assets/StandardAssets.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "Scene/Scene.hpp"
#include "Debug/Internal_Log.hpp"
#include "Assets/Internal_AssetManager.hpp"

#include <Windows.h>

namespace Parrot
{
	static Window* s_MainWindow = nullptr;
	static Window* s_BoundWindow = nullptr;
	static std::unordered_map<std::string, Window*> s_Windows;
	static std::unordered_map<std::string, ScriptCreationFunc> s_Scripts;
	static Utils::Stopwatch s_ApplicationTimer;

	namespace Application
	{
		Window& GetWindow(const std::string& tag)
		{
			Internal_Log::LogAssert(s_Windows.find(tag) != s_Windows.end(), "Window \"%\" doesn't exist!", tag);
			return *s_Windows[tag];
		}
		Window& GetBoundWindow()
		{
			Internal_Log::LogAssert(s_BoundWindow, "No Window was bound so far or the bound window was closed!");
			return *s_BoundWindow;
		}
		Window& GetMainWindow()
		{
			Internal_Log::LogAssert(s_MainWindow, "Main Window got destroyed already or wasn't created yet!");
			return *s_MainWindow;
		}
		bool HasWindow(const std::string& tag)
		{
			return s_Windows.find(tag) != s_Windows.end();
		}
		Utils::Timestep AbsTime()
		{
			return s_ApplicationTimer.Timing();
		}
	}

	namespace Internal_Application
	{
		void AddScriptCreationFunc(const std::string& tag, ScriptCreationFunc func)
		{
			s_Scripts[tag] = func;
		}
		ScriptCreationFunc GetScriptCreationFunc(const std::string& tag)
		{
			Internal_Log::LogAssert(s_Scripts.find(tag) != s_Scripts.end(), "Script \"%\" doesn't exist!", tag);
			return *s_Scripts[tag];
		}
		void AddWindow(const std::string& tag, Window* window)
		{
			if (s_Windows.empty())
				s_MainWindow = window;
			s_Windows[tag] = window;
		}
		void SetBoundWindow(Window* window)
		{
			s_BoundWindow = window;
		}
	}
	void RemoveWindow(Window* window)
	{
		if (s_MainWindow == window)
			s_MainWindow = nullptr;
		if (s_BoundWindow == window)
			s_BoundWindow = nullptr;
		s_Windows.erase(window->GetTag());
	}
}

using namespace Parrot;
int main()
{
	HWND hWnd = GetConsoleWindow();
#ifdef PT_SHOW_CONSOLE
	ShowWindow(hWnd, SW_SHOW);
#else 
	ShowWindow(hWnd, SW_HIDE);
#endif // PT_SHOW_CONSOLE

	s_ApplicationTimer.Start();
	
	Internal_Log::StartScope("ParrotInit");

	Asset::CreateStandardAssets();
	Internal_Log::LogInfo("Standard Assets created successfully!");
	
	Internal_Application::OnCreate();
	
	Internal_Log::LogInfo("MeshRenderer initialized successfully!");
	
	Internal_Log::EndScope();

	Internal_Log::StartScope("Runtime");
	while (s_MainWindow && s_MainWindow->IsOpen())
	{
		for (auto& pair : s_Windows)
		{
			Window* window = pair.second;
			if (window->IsOpen())
			{
				window->Bind();
				window->Clear();
				window->GetLoadedScene().UpdateObjs();
				window->GetLoadedScene().Render();
				window->Refresh();
			}
			else
			{
				RemoveWindow(pair.second);
				delete window;
				break;
			}
		}
	}	
	Internal_Log::EndScope();
	for (auto& pair : s_Windows)
		delete pair.second;
	Internal_Log::LogInfo("Parrot terminated successfully after %s!", s_ApplicationTimer.Timing().Seconds());
	(void)std::getchar();
}