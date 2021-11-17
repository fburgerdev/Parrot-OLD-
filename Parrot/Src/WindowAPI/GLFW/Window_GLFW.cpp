#include "Ptpch.hpp"
#include "glad/glad.h"
#include "Window_GLFW.hpp"
#include "Debug/InternalLog.hpp"
#include "Input/InternalInput.hpp"
#include "ClientInterface/Application.hpp"

namespace Parrot
{
	static std::unordered_map<GLFWwindow*, std::stack<Event>> s_EventMap;

	Window_GLFW::Window_GLFW(const std::string& title, const Math::Vec2u& dim)
		: m_Window(nullptr), m_Title(title)
	{
		InternalLog::LogAssert(glfwInit(), "GLFW initialization failed!");
		InternalLog::LogInfo("GLFW initialization successful!");

		m_Window = glfwCreateWindow(dim.x, dim.y, title.c_str(), nullptr, nullptr);
		InternalLog::LogAssert(m_Window, "Window \"%\" creation failed!", title);
		InternalLog::LogInfo("Window \"%\" creation successful!", title);
		Bind();

		InternalLog::LogAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "GLAD initialization failed!");
		InternalLog::LogInfo("GLAD initialization successful!");

	    // Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
	    {
	    	glViewport(0, 0, width, height);
	    	Event e(Event::Type::WindowResizeEvent);
	    	e.windowResizeEvent.dim = Math::Vec2u((uint32_t)width, (uint32_t)height);
			s_EventMap[window].push(e);
	    });
	    glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int32_t state)
	    {
	    	Event e(Event::Type::WindowMaximizeEvent);
			s_EventMap[window].push(e);
			});
	    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	    {
	    	Event e(Event::Type::WindowCloseRequestEvent);
			s_EventMap[window].push(e);
		});
	    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
	    {
	    	Event e(Event::Type::MouseMoveEvent);
	    	e.mouseMoveEvent.pos = Math::Vec2u((uint32_t)x, (uint32_t)y);
			s_EventMap[window].push(e);
		});
	    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
	    {
	    	Event e(Event::Type::MouseButtonEvent);
	    	e.mouseButtonEvent.button = (MouseButton)button;
	    	e.mouseButtonEvent.state = (MouseButtonState)action;
	    	SetMouseButtonState(e.mouseButtonEvent.button, e.mouseButtonEvent.state);
			s_EventMap[window].push(e);
	    });
	    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	    {
	    	Event e(Event::Type::MouseScrollEvent);
	    	e.mouseScrollEvent.xOffset = (int32_t)xOffset;
			e.mouseScrollEvent.yOffset = (int32_t)yOffset;
			s_EventMap[window].push(e);
	    });
	    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
	    {
	    	Event e(Event::Type::KeyboardEvent);
	    	e.keyboardEvent.keyCode = (KeyCode)key;
	    	e.keyboardEvent.state = (KeyState)action;
	    	SetKeyboardKeyState(e.keyboardEvent.keyCode, e.keyboardEvent.state);
			s_EventMap[window].push(e);
	    });
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int32_t focus)
		{
			Event e(Event::Type::WindowGotFocus);
			if (focus == GLFW_FALSE)
				e.type = Event::Type::WindowLostFocus;
			s_EventMap[window].push(e);
		});
	    glfwSwapInterval(1);
	}

	Window_GLFW::~Window_GLFW()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window_GLFW::Bind() const
	{
		if (glfwGetCurrentContext() != m_Window)
			glfwMakeContextCurrent(m_Window);
	}
	void Window_GLFW::SetTitle(const std::string& title)
	{
		m_Title = title;
		Bind();
		glfwSetWindowTitle(m_Window, title.c_str());
	}
	const std::string& Window_GLFW::GetTitle() const
	{
		return m_Title;
	}

	void Window_GLFW::SetCursorPos(const Math::Vec2i& pos)
	{
		Bind();
		glfwSetCursorPos(m_Window, (double)pos.x, (double)pos.y);
	}
	Math::Vec2i Window_GLFW::GetCursorPos() const
	{
		double x, y;
		Bind();
		glfwGetCursorPos(m_Window, &x, &y);
		return Math::Vec2i((int32_t)x, (int32_t)y);
	}

	void Window_GLFW::Maximize()
	{
		Bind();
		glfwMaximizeWindow(m_Window);
	}
	void Window_GLFW::Minimize()
	{
		Bind();
		glfwIconifyWindow(m_Window);
	}

	void Window_GLFW::SetSize(const Math::Vec2u& dim)
	{
		Bind();
		glfwSetWindowSize(m_Window, (int32_t)dim.x, (int32_t)dim.y);
	}
	Math::Vec2u Window_GLFW::GetSize() const
	{
		int width, height;
		Bind();
		glfwGetWindowSize(m_Window, &width, &height);
		return Math::Vec2u((uint32_t)width, (uint32_t)height);
	}
	void Window_GLFW::Update()
	{
		Bind();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window_GLFW::Clear()
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window_GLFW::PollEvent(Event& e)
	{
		std::stack<Event>& stack = s_EventMap[m_Window];
		if (stack.empty())
			return false;
		e = stack.top();
		stack.pop();
		return true;
	}
}