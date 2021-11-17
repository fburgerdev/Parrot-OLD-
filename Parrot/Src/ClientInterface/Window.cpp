#include "Ptpch.hpp"
#include "Window.hpp"
#include "InternalApplication.hpp"
#include "WindowAPI/WindowAPI.hpp"
#include "Assets/AssetManager.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Window::Window(const PtWindow& ptWindow)
		: m_Tag(ptWindow.GetFilepath().GetFilename().GetName()), m_WindowAPI(CreateWindowAPI(m_Tag, ptWindow.GetData().size)), m_ShouldClose(false), m_Scene(nullptr)
	{
		Application::AddWindow(m_Tag, this);
		m_Scene = new Scene(*this, AssetManager::GetSceneAsset(ptWindow.GetData().scene));
	}
	
	Window::~Window()
	{
		UnloadScene();
		Application::RemoveWindow(m_Tag);
		delete m_WindowAPI;
	}
	const std::string& Window::GetTag() const
	{
		return m_Tag;
	}

	bool Window::ShouldClose() const
	{
		return m_ShouldClose;
	}
	void Window::Close()
	{
		m_ShouldClose = true;
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

	WindowAPI& Window::GetWindowAPI()
	{
		return *m_WindowAPI;
	}
}
