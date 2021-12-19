#include "Ptpch.hpp"
#include "Application.hpp"
#include "Debug/Debugstream.hpp"
#include "Assets/DefaultAssets.hpp"
#include "Scene/Scene.hpp"

namespace Parrot
{
	static Window* s_MainWindow = nullptr;
	static Window* s_BoundWindow = nullptr;
	static bool s_Terminate = false;
	static std::unordered_map<std::string, Window*> s_Windows;
	static std::unordered_map<std::string, ScriptCreationFunc> s_Scripts;
	static Utils::Stopwatch s_ApplicationTimer;

	namespace Application
	{
		Window& GetWindow(const std::string& tag)
		{
			if (PT_FUNC_GUARDS_ENABLED && s_Windows.find(tag) == s_Windows.end())
			{
				DebugOut << WindowLookupWarning << "Unknown Window: " << tag << Debugstream::EndMsg;
			}
			return *s_Windows[tag];
		}
		Window& MainWindow()
		{
			return *s_MainWindow;
		}
		bool HasWindow(const std::string& tag)
		{
			return s_Windows.find(tag) != s_Windows.end();
		}
		Utils::Timestep AbsTime()
		{
			return s_ApplicationTimer.Ts();
		}
	}

	void Internal_AddScriptCreationFunc(const std::string& tag, ScriptCreationFunc func)
	{
		s_Scripts[tag] = func;
	}
	ScriptCreationFunc Internal_GetScriptCreationFunc(const std::string& tag)
	{
		return *s_Scripts[tag];
	}
	void Internal_AddWindow(Window* window)
	{
		if (s_Windows.empty())
			s_MainWindow = window;
		s_Windows[window->GetTag()] = window;
	}
	Window& Internal_GetBoundWindow()
	{
		return *s_BoundWindow;
	}
	void Internal_SetBoundWindow(Window* window)
	{
		s_BoundWindow = window;
	}
	void Internal_RemoveWindow(Window* window)
	{
		if (s_MainWindow == window)
			s_MainWindow = nullptr;
		if (s_BoundWindow == window)
			s_BoundWindow = nullptr;
		s_Windows.erase(window->GetTag());
	}
}

namespace Parrot
{
	void OnCreate();
}

using namespace Parrot;
int main()
{
	s_ApplicationTimer.Reset();
	Asset::CreateDefaultAssets();
	OnCreate();
	Utils::Stopwatch frameWatch;
	while (!s_Terminate)
	{
		float frameSecs = frameWatch.Ts().Sec();
		frameWatch.Reset();
		for (auto&[tag, window] : s_Windows)
		{
			if (!s_MainWindow->IsOpen())
			{
				s_Terminate = true;
				break;
			}
			if (window->IsOpen())
			{
				window->Bind();
				window->Clear();
				window->LoadedScene().UpdateObjs();
				window->LoadedScene().Render();
				window->Refresh();
			}
			else
			{
				Internal_RemoveWindow(window);
				delete window;
				break;
			}
		}
	}	
	for (auto&[tag, window] : s_Windows)
		delete window;
	DebugOut << "Parrot terminated successfully after " << s_ApplicationTimer.Ts().Sec() << "s." << Debugstream::EndMsg;
	(void)std::getchar();
}