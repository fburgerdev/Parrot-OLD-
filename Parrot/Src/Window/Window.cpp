#include "Ptpch.hpp"
#include "Window.hpp"
#include "WindowAPI.hpp"

namespace Parrot
{
	Window::Window(const std::string& name, Math::Vec2u dim)
		: m_Name(name), m_WindowAPI(CreateWindowAPI(name, dim)), m_ShouldClose(false), m_LoadedScene(nullptr)
	{
		OnCreate();
	}
	
	Window::~Window()
	{
		delete reinterpret_cast<WindowAPI*>(m_WindowAPI);
	}

	bool Window::ShouldClose()
	{
		return m_ShouldClose;
	}
	void Window::Close()
	{
		m_ShouldClose = true;
	}

	/*void Window::LoadScene(const char* name)
	{

	}
	Scene& Window::LoadedScene()
	{

	}

	Scene& Window::CreateScene(const char* name)
	{

	}
	void Window::DestroyScene(const char* name)
	{

	}
	Scene& Window::GetScene(const char* name)
	{

	}*/

	// WindowAPI
	void Window::ShowFrames(bool state)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->ShowFrames(state);
	}
	void Window::SetTitle(const std::string& title)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->SetTitle(title);
	}
	const std::string& Window::GetTitle()
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		return reinterpret_cast<WindowAPI*>(m_WindowAPI)->GetTitle();
	}

	void Window::SetCursorPos(Math::Vec2i pos)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->SetCursorPos(pos);
	}
	Math::Vec2i Window::GetCursorPos()
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
	Math::Vec2u Window::GetSize()
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		return reinterpret_cast<WindowAPI*>(m_WindowAPI)->GetSize();
	}

	void Window::Framerate(uint32_t rate)
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Framerate(rate);
	}
	void Window::Update()
	{
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Bind();
		reinterpret_cast<WindowAPI*>(m_WindowAPI)->Update();
	}
}
