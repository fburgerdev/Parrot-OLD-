#include "Ptpch.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "WindowAPI/WindowAPI.hpp"

namespace Parrot
{
	// defined in "Application.cpp"
	void HIDDEN_ApplicationAddWindow(const std::string& tag, Window* window);
	void HIDDEN_ApplicationRemoveWindow(const std::string& tag);
	
	// class
	Window::Window(const std::string& tag, Math::Vec2u size)
		: m_Tag(tag), m_WindowAPI(CreateWindowAPI(tag, size, this)), m_ShouldClose(false), m_LoadedScene(nullptr)
	{
		HIDDEN_ApplicationAddWindow(tag, this);
	}
	
	Window::~Window()
	{
		UnloadScene();
		HIDDEN_ApplicationRemoveWindow(m_Tag);
		delete reinterpret_cast<WindowAPI*>(m_WindowAPI);
	}

	bool Window::ShouldClose() const
	{
		return m_ShouldClose;
	}
	void Window::Close()
	{
		m_ShouldClose = true;
	}

	Scene& Window::LoadScene(const std::string& tag)
	{
		Scene& scene = Application::GetScene(tag);
		LoadScene(scene);
		return scene;
	}
	void Window::LoadScene(Scene& scene)
	{
		if (m_LoadedScene)
			UnloadScene();
		m_LoadedScene = &scene;
	}
	void Window::UnloadScene()
	{
		if (!m_LoadedScene)
			return;
		m_LoadedScene = nullptr;
	}

	// WindowAPI
	void Window::SetTitle(const std::string& title)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->SetTitle(title);
	}
	const std::string& Window::GetTitle() const
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		return reinterpret_cast<WindowAPI*>(m_WindowAPI)->GetTitle();
	}

	void Window::SetCursorPos(Math::Vec2i pos)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->SetCursorPos(pos);
	}
	Math::Vec2i Window::GetCursorPos() const
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		return reinterpret_cast<WindowAPI*>(m_WindowAPI)->GetCursorPos();
	}

	void Window::Maximize() 
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Maximize();
	}
	void Window::Minimize()
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Minimize();
	}

	void Window::SetSize(Math::Vec2u dim)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->SetSize(dim);
	}
	Math::Vec2u Window::GetSize() const
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		return reinterpret_cast<WindowAPI*>(m_WindowAPI)->GetSize();
	}

	void Window::Update()
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		if (m_LoadedScene)
		{
			m_LoadedScene->UpdateObjs();
			m_LoadedScene->Render();
		}
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Update();
	}
}
