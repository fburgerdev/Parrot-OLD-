#include "Ptpch.hpp"
#include "glad/glad.h"
#include "Window_GLFW.hpp"
#include "Debug/Log.hpp"
#include "Input/Input.hpp"
#include "Input/Event.hpp"

namespace Parrot
{
	// defined in "Input.cpp"
	void SetMouseButtonState(Mouse::Button button, Mouse::ButtonState state);
	void SetKeyboardKeyState(Keyboard::KeyCode keyCode, Keyboard::KeyState state);

	// defined in "Event.cpp"
	void PushEvent(Event e);

	static uint32_t s_WindowCount = 0;
	Window_GLFW::Window_GLFW(const std::string& name, Math::Vec2u dim)
		: m_Window(nullptr), m_Title("Untitled"), m_Framerate(60), m_ShowFrames(true)
	{
		if (s_WindowCount == 0)
		{
			Log::LogAssert(glfwInit(), "GLFW initialization failed!");
			Log::LogInfo("GLFW initialization successful!");
		}

		m_Window = glfwCreateWindow(dim.x, dim.y, name.c_str(), nullptr, nullptr);
		Log::LogAssert(m_Window, "Window creation failed!");
		Log::LogInfo("Window creation successful!");
		glfwMakeContextCurrent(m_Window);
		s_WindowCount++;

		Log::LogAssert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "GLAD initialization failed!");
		Log::LogInfo("GLAD initialization successful!");

	    // Callbacks
	    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
	    {
	    	glViewport(0, 0, width, height);
	    	Event e(Event::Type::WindowResizeEvent);
	    	e.windowResizeEvent.dim = Math::Vec2u((uint32_t)width, (uint32_t)height);
			PushEvent(e);
	    });
	    glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int32_t state)
	    {
	    	if (state == GLFW_PRESS)
	    	{
	    		Event e(Event::Type::WindowMaximizeEvent);
				PushEvent(e);
	    	}
	    });
	    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
	    {
	    	Event e(Event::Type::WindowCloseRequestEvent);
			PushEvent(e);
	    });
	    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
	    {
	    	Event e(Event::Type::MouseMoveEvent);
	    	e.mouseMoveEvent.pos = Math::Vec2u((uint32_t)x, (uint32_t)y);
			PushEvent(e);
		});
	    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
	    {
	    	Event e(Event::Type::MouseButtonEvent);
	    	e.mouseButtonEvent.button = (Mouse::Button)button;
	    	e.mouseButtonEvent.state = (Mouse::ButtonState)action;
	    	SetMouseButtonState(e.mouseButtonEvent.button, e.mouseButtonEvent.state);
			PushEvent(e);
	    });
	    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
	    {
	    	Event e(Event::Type::MouseScrollEvent);
	    	e.mouseScrollEvent.xOffset = (int32_t)xOffset;
			e.mouseScrollEvent.yOffset = (int32_t)yOffset;
			PushEvent(e);
	    });
	    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
	    {
	    	Event e(Event::Type::KeyboardEvent);
	    	e.keyboardEvent.keyCode = (Keyboard::KeyCode)key;
	    	e.keyboardEvent.state = (Keyboard::KeyState)action;
	    	SetKeyboardKeyState(e.keyboardEvent.keyCode, e.keyboardEvent.state);
			PushEvent(e);
	    });
	    glfwSwapInterval(0);
	}

	Window_GLFW::~Window_GLFW()
	{
		glfwDestroyWindow(m_Window);
		s_WindowCount--;
		if (s_WindowCount == 0)
			glfwTerminate();
	}

	void Window_GLFW::Bind()
	{
		glfwMakeContextCurrent(m_Window);
	}
	void Window_GLFW::ShowFrames(bool state)
	{
		m_ShowFrames = state;
		glfwSetWindowTitle(m_Window, m_Title.c_str());
		UpdateTitleFrames();
	}
	void Window_GLFW::SetTitle(const std::string& title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
		UpdateTitleFrames();
	}
	const std::string& Window_GLFW::GetTitle()
	{
		return m_Title;
	}

	void Window_GLFW::SetCursorPos(Math::Vec2i pos)
	{
		glfwSetCursorPos(m_Window, (double)pos.x, (double)pos.y);
	}
	Math::Vec2i Window_GLFW::GetCursorPos()
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
		SetSize(Math::Vec2u(0));
	}

	void Window_GLFW::SetSize(Math::Vec2u dim)
	{
		glfwSetWindowSize(m_Window, (int32_t)dim.x, (int32_t)dim.y);
	}
	Math::Vec2u Window_GLFW::GetSize()
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return Math::Vec2u((uint32_t)width, (uint32_t)height);
	}

	void Window_GLFW::Framerate(uint32_t framerate)
	{
		m_Framerate = framerate;
	}
	void Window_GLFW::Update()
	{
		UpdateTitleFrames();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
		Log::LogInfo("Updated");
		/*if (m_Framerate != 0)
		{
			while (m_FrameWatch.Timing().Seconds() < 1.0f / m_Framerate)
				continue;
		}
		m_FrameWatch.Start();*/
	}

	void Window_GLFW::UpdateTitleFrames()
	{
		//Utils::Timestep currentTime = AbsTime();
		//
		//static uint32_t frameCount = 0;
		//static Utils::Timestep previousTime = currentTime;
		//
		//frameCount++;
		//if (currentTime.Seconds() - previousTime.Seconds() >= 1.f)
		//{
		//	if (m_ShowFrames)
		//	{
		//		uint32_t timeInMS = (uint32_t)(10000.0f / frameCount);
		//		std::string titleWithFPS = std::string(m_Title) + " [" + std::to_string(frameCount) + " FPS, " + std::to_string((uint32_t)(1000.0f / frameCount)) + " ms]";
		//
		//		glfwSetWindowTitle(m_Window, titleWithFPS.c_str());
		//	}
		//	frameCount = 0;
		//	previousTime = currentTime;
		//}
	}
}