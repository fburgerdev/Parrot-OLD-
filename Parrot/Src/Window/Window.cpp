#include "Ptpch.hpp"
#include "Window.hpp"

#include "Scene/Scene.hpp"
#include "Assets/AssetManager.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	void Internal_AddWindow(Window* window);
	Window::Window(const Asset::WindowAsset& asset)
		: PtObj(asset.GetTag()), m_IsOpen(true), m_Scene(nullptr)
	{
		Internal_AddWindow(this);
		m_Scene = new Scene(*this, *asset.scene);
	}
	
	Window::~Window()
	{
		UnloadScene();
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
	Scene& Window::LoadedScene()
	{
		return *m_Scene;
	}
	void Window::UnloadScene()
	{
		if (!m_Scene)
			return;
		delete m_Scene;
	}
	
	Window& CreateWindow(const Asset::WindowAsset& asset)
	{
		Window* window;
	#ifdef PT_GLFW
		window = new Window_GLFW(asset);
	#elif
		#error No WindowAPI specified! Options: "PT_GLFW"
	#endif
		return *window;
	}
}
