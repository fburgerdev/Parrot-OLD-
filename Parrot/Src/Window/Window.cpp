#include "Ptpch.hpp"
#include "Window.hpp"
#include "WindowAPI.hpp"

namespace Parrot
{
	void Window::Maximize()
	{
		WindowAPI::GetContext()->Maximize();
	}
	void Window::ShowFrames(bool state)
	{
		WindowAPI::GetContext()->ShowFrames(state);
	}
	void Window::Resize(Math::Vec2u dim)
	{
		WindowAPI::GetContext()->Resize(dim);
	}
	Math::Vec2u Window::GetSize()
	{
		return WindowAPI::GetContext()->GetSize();
	}
	void Window::Display()
	{
		WindowAPI::GetContext()->Display();
	}

	void Window::SetCursorPos(Math::Vec2i pos)
	{
		WindowAPI::GetContext()->SetCursorPos(pos);
	}
	Math::Vec2i Window::GetCursorPos()
	{
		return WindowAPI::GetContext()->GetCursorPos();
	}
}