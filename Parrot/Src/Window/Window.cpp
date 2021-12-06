#include "Ptpch.hpp"
#include "Window.hpp"

#include "Scene/Scene.hpp"
#include "Assets/AssetManager.hpp"
#include "GLFW/Window_GLFW.hpp"
#include "Debug/Internal_Log.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	static std::unordered_map<std::string, uint32_t> s_WindowNamesakeCount;
	Window::Window(const Asset::WindowAsset& WindowAsset)
		: PtObj(PtObj::Type::Window), m_Tag(WindowAsset.filepath.GetFilename().GetName()), m_IsOpen(true), m_Scene(nullptr)
	{
		if (s_WindowNamesakeCount.find(m_Tag) == s_WindowNamesakeCount.end())
			s_WindowNamesakeCount[m_Tag] = 0;
		else
		{
			uint32_t number = ++s_WindowNamesakeCount[m_Tag];
			m_Tag += '(' + std::to_string(number) + ')';
		}
		Internal_Application::AddWindow(m_Tag, this);
		m_Scene = new Scene(*this, *WindowAsset.scene);
	}
	
	Window::~Window()
	{
		s_WindowNamesakeCount[m_Tag]--;
		UnloadScene();
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

	Scene& Window::LoadScene(const Asset::SceneAsset& scene)
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
		Internal_Log::LogAssert(m_Scene, "No Scene loaded in window \"%\"!", m_Tag);
		return *m_Scene;
	}
	void Window::UnloadScene()
	{
		if (!m_Scene)
			return;
		delete m_Scene;
	}
	
	Window& OpenWindow(const Asset::WindowAsset& WindowAsset)
	{
		Window* window;
	#ifdef PT_GLFW
		window = new Window_GLFW(WindowAsset);
	#elif
		#error No WindowAPI specified! Options: "PT_GLFW"
	#endif
		return *window;
	}
}
