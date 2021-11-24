#include "Ptpch.hpp"
#include "Assets/InternalAssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "InternalApplication.hpp"
#include "Scene/Scene.hpp"

namespace Parrot
{
	static Window* s_MainWindow = nullptr;
	static Window* s_BoundWindow = nullptr;
	static std::unordered_map<std::string, Window*> s_Windows;
	static std::unordered_map<std::string, ScriptCreationFunc> s_Scripts;
	static Utils::Stopwatch s_ApplicationTimer;

	namespace Application
	{
		// Application.hpp
		Window& GetWindow(const std::string& tag)
		{
			InternalLog::LogAssert(s_Windows.find(tag) != s_Windows.end(), "Window \"%\" doesn't exist!", tag);
			return *s_Windows[tag];
		}
		Window& GetBoundWindow()
		{
			InternalLog::LogAssert(s_BoundWindow, "No Window was bound so far!");
			return *s_BoundWindow;
		}
		Window& MainWindow()
		{
			InternalLog::LogAssert(s_MainWindow, "Main Window got destroyed already or wasn't created yet!");
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

		// InternalApplication.hpp
		void Internal_AddScript(const std::string& tag, ScriptCreationFunc func)
		{
			s_Scripts[tag] = func;
		}
		ScriptCreationFunc Internal_GetScript(const std::string& tag)
		{
			InternalLog::LogAssert(s_Scripts.find(tag) != s_Scripts.end(), "Script \"%\" doesn't exist!", tag);
			return *s_Scripts[tag];
		}
		void Internal_AddWindow(const std::string& tag, Window* window)
		{
			if (s_Windows.empty())
				s_MainWindow = window;
			s_Windows[tag] = window;
		}
		void Internal_RemoveWindow(const std::string& tag)
		{
			Window* window = s_Windows[tag];
			if (s_MainWindow == window)
				s_MainWindow = nullptr;
			if (s_BoundWindow == window)
				s_BoundWindow = nullptr;
			s_Windows.erase(tag);
		}
		void Internal_SetBoundWindow(Window* window)
		{
			s_BoundWindow = window;
		}
	}

	void UpdateScene(Scene& scene);
	void RenderScene(Scene& scene);
}

using namespace Parrot;
int main()
{
	s_ApplicationTimer.Start();
	
	InternalLog::StartScope("ParrotInit");
	AssetManager::Internal_InitAssetDir(Utils::Directory("..\\Parrot\\Src\\Assets\\Defaults\\"));
	AssetManager::Internal_LoadAllFromDir();
	InternalLog::LogInfo("Default Assets loaded successfully!");
	InternalLog::EndScope();

	AssetManager::Internal_ConvertToAsset(Utils::Filepath("..\\TestAssets\\Skybox.png"));
	InternalLog::StartScope("OnCreate");
	Application::Internal_OnCreate();
	MeshRenderer::Init();
	InternalLog::LogInfo("MeshRenderer initialized successfully!");
	InternalLog::LogAssert(s_MainWindow, "\"Application::OnCreate()\" needs to create at least one Window!");
	InternalLog::EndScope();

	InternalLog::StartScope("Runtime");
	while (s_MainWindow && s_MainWindow->IsOpen())
	{
		for (auto& pair : s_Windows)
		{
			Window& window = *pair.second;
			if (window.IsOpen())
			{
				window.Bind();
				window.Clear();
				Scene& scene = window.GetLoadedScene();
				if (!scene.m_OnCreateCalled)
				{
					for (Script* script : scene.m_Scripts)
					{
						script->OnCreate();
					}
					scene.m_OnCreateCalled = true;
				}
				for (Script* script : scene.m_Scripts)
					script->OnUpdate();
				for (auto& pair : scene.m_SceneObjs)
				{
					if (pair.second->HasComponent(ComponentType::Camera))
					{
						MeshRenderer::StartCoroutine(pair.second->GetComponent<Camera>());
						break;
					}
				}
				for (auto& pair : scene.m_SceneObjs)
				{
					if (pair.second->HasComponent(ComponentType::Renderobj))
					{
						MeshRenderer::Push(pair.second->transform, pair.second->GetComponent<Renderobj>());
					}
				}
				window.Refresh();
			}
			else
			{
				delete pair.second;
				break;
			}
		}
	}	
	InternalLog::EndScope();
	if (s_MainWindow)
		delete s_MainWindow;
	InternalLog::LogInfo("Parrot terminated successfully after %s!", s_ApplicationTimer.Timing().Seconds());
}