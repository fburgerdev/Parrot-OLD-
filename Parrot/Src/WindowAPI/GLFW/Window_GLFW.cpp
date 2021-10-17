#include "Ptpch.hpp"
#include "glad/glad.h"
#include "Window_GLFW.hpp"
#include "Debug/InternalLog.hpp"
#include "Input/Input.hpp"
#include "ClientInterface/Application.hpp"

namespace Parrot
{
	static std::unordered_map<GLFWwindow*, Window*> s_WindowLookup;

	// defined in "Input.cpp"
	void HIDDEN_SetMouseButtonState(Mouse::Button button, Mouse::ButtonState state);
	void HIDDEN_SetKeyboardKeyState(Keyboard::KeyCode keyCode, Keyboard::KeyState state);

	Window_GLFW::Window_GLFW(const std::string& title, Math::Vec2u dim, Window* window)
		: m_Window(nullptr), m_Title(title),  m_ShowFrames(true)
	{
		if (s_WindowLookup.empty())
		{
			InternalLog::LogAssert(glfwInit(), "GLFW initialization failed!");
			InternalLog::LogInfo("GLFW initialization successful!");
		}

		m_Window = glfwCreateWindow(dim.x, dim.y, title.c_str(), nullptr, nullptr);
		InternalLog::LogAssert(m_Window, "Window \"%\" creation failed!", title);
		InternalLog::LogInfo("Window \"%\" creation successful!", title);
		glfwMakeContextCurrent(m_Window);
		s_WindowLookup[m_Window] = window;

		InternalLog::LogAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "GLAD initialization failed!");
		InternalLog::LogInfo("GLAD initialization successful!");

	    // Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
	    {
	    	glViewport(0, 0, width, height);
	    	Event e(Event::Type::WindowResizeEvent);
	    	e.windowResizeEvent.dim = Math::Vec2u((uint32_t)width, (uint32_t)height);
			s_WindowLookup[window]->OnEvent(e);
	    });
	    glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int32_t state)
	    {
	    	Event e(Event::Type::WindowMaximizeEvent);
			s_WindowLookup[window]->OnEvent(e);
	    });
	    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	    {
	    	Event e(Event::Type::WindowCloseRequestEvent);
			s_WindowLookup[window]->OnEvent(e);
		});
	    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
	    {
	    	Event e(Event::Type::MouseMoveEvent);
	    	e.mouseMoveEvent.pos = Math::Vec2u((uint32_t)x, (uint32_t)y);
			s_WindowLookup[window]->OnEvent(e);
		});
	    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
	    {
	    	Event e(Event::Type::MouseButtonEvent);
	    	e.mouseButtonEvent.button = (Mouse::Button)button;
	    	e.mouseButtonEvent.state = (Mouse::ButtonState)action;
	    	HIDDEN_SetMouseButtonState(e.mouseButtonEvent.button, e.mouseButtonEvent.state);
			s_WindowLookup[window]->OnEvent(e);
	    });
	    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	    {
	    	Event e(Event::Type::MouseScrollEvent);
	    	e.mouseScrollEvent.xOffset = (int32_t)xOffset;
			e.mouseScrollEvent.yOffset = (int32_t)yOffset;
			s_WindowLookup[window]->OnEvent(e);
	    });
	    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
	    {
	    	Event e(Event::Type::KeyboardEvent);
	    	e.keyboardEvent.keyCode = (Keyboard::KeyCode)key;
	    	e.keyboardEvent.state = (Keyboard::KeyState)action;
	    	HIDDEN_SetKeyboardKeyState(e.keyboardEvent.keyCode, e.keyboardEvent.state);
			s_WindowLookup[window]->OnEvent(e);
	    });
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int32_t focus)
		{
			Event e(Event::Type::WindowGotFocus);
			if (focus == GLFW_FALSE)
				e.type = Event::Type::WindowLostFocus;
			s_WindowLookup[window]->OnEvent(e);
		});
	    glfwSwapInterval(0);
	}

	Window_GLFW::~Window_GLFW()
	{
		s_WindowLookup.erase(m_Window);
		glfwDestroyWindow(m_Window);
		if (s_WindowLookup.empty())
			glfwTerminate();
	}

	void Window_GLFW::Bind() const
	{
		glfwMakeContextCurrent(m_Window);
	}
	void Window_GLFW::SetTitle(const std::string& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
	}
	const std::string& Window_GLFW::GetTitle() const
	{
		return m_Title;
	}

	void Window_GLFW::SetCursorPos(Math::Vec2i pos)
	{
		glfwSetCursorPos(m_Window, (double)pos.x, (double)pos.y);
	}
	Math::Vec2i Window_GLFW::GetCursorPos() const
	{
		double x, y;
		glfwGetCursorPos(m_Window, &x, &y);
		return Math::Vec2i((int32_t)x, (int32_t)y);
	}

	void Window_GLFW::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}
	void Window_GLFW::Minimize()
	{
		glfwIconifyWindow(m_Window);
	}

	void Window_GLFW::SetSize(Math::Vec2u dim)
	{
		glfwSetWindowSize(m_Window, (int32_t)dim.x, (int32_t)dim.y);
	}
	Math::Vec2u Window_GLFW::GetSize() const
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return Math::Vec2u((uint32_t)width, (uint32_t)height);
	}
	void Window_GLFW::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}