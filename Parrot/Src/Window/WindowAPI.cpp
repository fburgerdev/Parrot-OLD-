#include "Ptpch.hpp"
#include "Core/Macros.hpp"
#include "WindowAPI.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	WindowAPI* WindowAPI::s_DefaultWindow;

	std::vector<WindowAPI*> s_CreatedWindows;
	WindowAPI* s_ContextWindow;

	WindowAPI* WindowAPI::Create(const char* title, Math::Vec2u dim, const WindowAPI::Config& config)
	{
		WindowAPI* window;
	#ifdef PT_GLFW
			return new Window_GLFW(title, dim, config);
	#else
		#error Parrot currently only supports GLFW as WindowAPI
	#endif
			s_CreatedWindows.push_back(window);
			return window;
	}

	void WindowAPI::SetContext(WindowAPI* window)
	{
		s_ContextWindow = window;
	}
	WindowAPI* WindowAPI::GetContext()
	{
		return s_ContextWindow;
	}
}