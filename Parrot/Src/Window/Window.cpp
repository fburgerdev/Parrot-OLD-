#include "Ptpch.hpp"
#include "Window.hpp"
#include "Scene/Scene.hpp"
#include "Core/InternalApplication.hpp"
#include "Assets/AssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	static std::unordered_map<std::string, uint32_t> s_WindowNamesakeCount;
	Window::Window(const PtWindow& ptWindow)
		: PtObj(PtObjType::Window), m_Tag(ptWindow.GetFilepath().GetFilename().GetName()), m_IsOpen(true), m_Scene(nullptr)
	{
		if (s_WindowNamesakeCount.find(m_Tag) == s_WindowNamesakeCount.end())
		{
			s_WindowNamesakeCount[m_Tag] = 0;
		}
		else
		{
			uint32_t number = ++s_WindowNamesakeCount[m_Tag];
			m_Tag += '(' + std::to_string(number) + ')';
		}

		Application::Internal_AddWindow(m_Tag, this);
		m_Scene = new Scene(*this, AssetManager::GetSceneAsset(ptWindow.GetData().scene));
	}
	
	Window::~Window()
	{
		s_WindowNamesakeCount[m_Tag]--;
		UnloadScene();
		Application::Internal_RemoveWindow(m_Tag);
	}
	const std::string& Window::GetTag() const
	{
		return m_Tag;
	}

	bool Window::IsOpen() const
	{
		return m_IsOpen;
	}
	void Window::Close()
	{
		m_IsOpen = false;
	}

	Scene& Window::LoadScene(const PtScene& scene)
	{
		UnloadScene();
		m_Scene = new Scene(*this, scene);
		return *m_Scene;
	}
	bool Window::IsSceneLoaded()
	{
		return m_Scene != nullptr;
	}
	Scene& Window::GetLoadedScene()
	{
		InternalLog::LogAssert(m_Scene, "No Scene loaded in window \"%\"!", m_Tag);
		return *m_Scene;
	}
	void Window::UnloadScene()
	{
		if (!m_Scene)
			return;
		delete m_Scene;
	}
	
	Window& CreateWindow(const PtWindow& ptWindow)
	{
	#ifdef PT_GLFW
		return *new Window_GLFW(ptWindow);
	#elif
		#error No WindowAPI specified! Options: "PT_GLFW"
	#endif
	}
}
