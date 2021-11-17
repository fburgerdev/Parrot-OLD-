#include "Ptpch.hpp"
#include "InternalApplication.hpp"
#include "Assets/InternalAssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"

namespace Parrot
{
	static Window* s_MainWindow = nullptr;
	static std::unordered_map<std::string, Window*> s_Windows;
	static std::unordered_map<std::string, ScriptCreationFunc> s_Scripts;
	static Utils::Stopwatch s_ApplicationTimer;

	static void InitParrot()
	{
		{
			std::ofstream stream("..//Parrot//Src//Assets//Defaults//Quad.MSH", std::ios::binary);
			MeshVertex vertices[4];
			vertices[2] = MeshVertex({ -0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f });
			vertices[1] = MeshVertex({ +0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f });
			vertices[0] = MeshVertex({ +0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f });
			vertices[3] = MeshVertex({ -0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f });
			bool quad = true;
			size_t size = 4;
			stream.write((char*)&quad, 1);
			stream.write((char*)&size, sizeof(size_t));
			stream.write((char*)vertices, sizeof(MeshVertex) * size);
			stream.close();
		}
		{
			std::ofstream stream("..//Parrot//Src//Assets//Defaults//Cube.MSH", std::ios::binary);
			MeshVertex vertices[24];
			vertices[0] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f });
			vertices[1] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f });
			vertices[2] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f });
			vertices[3] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f });

			vertices[6] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f });
			vertices[5] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f });
			vertices[4] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f });
			vertices[7] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f });

			vertices[8 ] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f });
			vertices[9 ] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f });
			vertices[10] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f });
			vertices[11] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f });

			vertices[14] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f });
			vertices[13] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f });
			vertices[12] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f });
			vertices[15] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f });

			vertices[16] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f });
			vertices[17] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f });
			vertices[18] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f });
			vertices[19] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f });

			vertices[22] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f });
			vertices[21] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f });
			vertices[20] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f });
			vertices[23] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f });
			bool quad = true;
			size_t size = 24;
			stream.write((char*)&quad, 1);
			stream.write((char*)&size, sizeof(size_t));
			stream.write((char*)vertices, sizeof(MeshVertex) * size);
			stream.close();
		}
	}

	namespace Application
	{
		// Application.hpp
		Window& GetWindow(const std::string& tag)
		{
			InternalLog::LogAssert(s_Windows.find(tag) != s_Windows.end(), "Window \"%\" doesn't exist!", tag);
			return *s_Windows[tag];
		}
		Window& MainWindow()
		{
			InternalLog::LogAssert(s_MainWindow, "Main Window got destroyed already or wasn't created yet!");
			return *s_MainWindow;
		}
		Utils::Timestep AbsTime()
		{
			return s_ApplicationTimer.Timing();
		}

		// InternalApplication.hpp
		void AddScript(const std::string& tag, ScriptCreationFunc func)
		{
			s_Scripts[tag] = func;
		}
		ScriptCreationFunc GetScript(const std::string& tag)
		{
			InternalLog::LogAssert(s_Scripts.find(tag) != s_Scripts.end(), "Script \"%\" doesn't exist!", tag);
			return *s_Scripts[tag];
		}
		void AddWindow(const std::string& tag, Window* window)
		{
			if (s_Windows.empty())
				s_MainWindow = window;
			s_Windows[tag] = window;
		}
		void RemoveWindow(const std::string& tag)
		{
			if (s_MainWindow == s_Windows[tag])
				s_MainWindow = nullptr;
			s_Windows.erase(tag);
		}
	}
}

using namespace Parrot;
int main()
{
	//InitParrot();
	s_ApplicationTimer.Start();
	
	InternalLog::StartScope("ParrotInit");
	AssetManager::InitAssetDir(Utils::Directory("..\\Parrot\\Src\\Assets\\Defaults\\"));
	AssetManager::LoadAllFromDir();
	InternalLog::LogInfo("Default Assets loaded successfully!");
	InternalLog::EndScope();

	InternalLog::StartScope("OnCreate");
	Application::OnCreate();
	MeshRenderer::Init();
	InternalLog::LogInfo("MeshRenderer initialized successfully!");
	InternalLog::EndScope();

	InternalLog::StartScope("Runtime");
	InternalLog::LogAssert(s_MainWindow, "\"Application::OnCreate()\" needs to create at least one Window!");
	while (s_MainWindow && !s_MainWindow->ShouldClose())
	{
		for (auto& pair : s_Windows)
		{
			Window& window = *pair.second;
			if (window.ShouldClose())
			{
				delete pair.second;
				break;
			}
			else
			{
				window.GetWindowAPI().Clear();
				if (window.IsSceneLoaded())
				{
					window.GetLoadedScene().UpdateObjs();
					window.GetLoadedScene().Render();
					Event e;
					while (window.GetWindowAPI().PollEvent(e))
						window.GetLoadedScene().HandleEvent(e);
				}
				window.GetWindowAPI().Update();
			}
		}
	}	
	InternalLog::EndScope();
	if (s_MainWindow)
		delete s_MainWindow;
	InternalLog::LogInfo("Parrot terminated successfully after %s!", s_ApplicationTimer.Timing().Seconds());
}