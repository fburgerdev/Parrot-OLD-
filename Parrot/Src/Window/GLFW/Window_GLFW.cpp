#include "Ptpch.hpp"
#include "glad/glad.h"
#include "Window_GLFW.hpp"
#include "Core/Macros.hpp"
#include "Input/Event.hpp"
#include "Core/Log.hpp"
#include "Core/HiddenFunctions.hpp"
#include "Core/Time.hpp"

namespace Parrot
{
	Window_GLFW::Window_GLFW(const char* title, Math::Vec2u dim, const WindowAPI::Config& config)
		: m_Window(nullptr), m_Title(title), m_ShowFrames(true)
	{
		PT_ASSERT_MSG_SUCCESS(glfwInit() == GL_TRUE, "GLFW failed to initialize!", "GLFW initialized successfully!");
		// Window creation
		glfwWindowHint(GLFW_RESIZABLE, config.resizable);
		m_Window = config.fullscreen ? glfwCreateWindow(dim.x, dim.y, title, glfwGetPrimaryMonitor(), NULL) : glfwCreateWindow(dim.x, dim.y, title, NULL, NULL);
		PT_ASSERT_MSG_SUCCESS(m_Window != nullptr, "Window creation failed!", "Window created successfully!");
		glfwMakeContextCurrent(m_Window);
		if (config.maximized)
			glfwMaximizeWindow(m_Window);

		PT_ASSERT_MSG_SUCCESS(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "GLAD failed to initialize!", "GLAD initialized successfully!");

		// Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				glViewport(0, 0, width, height);
				Input::Event e(Input::Event::Type::WindowResizeEvent);
				e.windowResizeEvent.dim = Math::Vec2u((uint32_t)width, (uint32_t)height);
				TriggerOnEvent(e);
			});
		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int32_t state)
			{
				if (state == GLFW_PRESS)
				{
					Input::Event e(Input::Event::Type::WindowMaximizeEvent);
					TriggerOnEvent(e);
				}
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				Input::Event e(Input::Event::Type::WindowCloseRequestEvent);
				TriggerOnEvent(e);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
			{
				Input::Event e(Input::Event::Type::MouseMoveEvent);
				e.mouseMoveEvent.diff = Math::Vec2u((uint32_t)x, (uint32_t)y);
				TriggerOnEvent(e);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
			{
				Input::Event e(Input::Event::Type::MouseButtonEvent);
				e.mouseButtonEvent.button = (Input::Mouse::MouseButton)button;
				e.mouseButtonEvent.state = (Input::Mouse::MouseButtonState)action;
				SetMouseButtonState(e.mouseButtonEvent.button, e.mouseButtonEvent.state);
				TriggerOnEvent(e);
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Input::Event e(Input::Event::Type::MouseScrollEvent);
				e.mouseScrollEvent.xOffset = (int32_t)xOffset;
				e.mouseScrollEvent.yOffset = (int32_t)yOffset;
				TriggerOnEvent(e);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				Input::Event e(Input::Event::Type::KeyboardEvent);
				e.keyboardEvent.key = (Input::Keyboard::Key)key;
				e.keyboardEvent.state = (Input::Keyboard::KeyState)action;
				SetKeyboardKeyState(e.keyboardEvent.key, e.keyboardEvent.state);
				TriggerOnEvent(e);
			});
		glfwSwapInterval(0);
		/*glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);*/
	}
	void Window_GLFW::Maximize()
	{
		glfwMaximizeWindow(m_Window);
	}
	void Window_GLFW::ShowFrames(bool state)
	{
		if (!state)
			glfwSetWindowTitle(m_Window, m_Title);
		m_ShowFrames = state;
	}
	void Window_GLFW::Resize(Math::Vec2u dim)
	{
		glfwSetWindowSize(m_Window, (int32_t)dim.x, (int32_t)dim.y);
	}
	Math::Vec2u Window_GLFW::GetSize()
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return Math::Vec2u((uint32_t)width, (uint32_t)height);
	}
	void Window_GLFW::Display()
	{
		UpdateTitleFrames();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window_GLFW::UpdateTitleFrames()
	{
		if (!m_ShowFrames)
			return;
		
		Tracking::Timestep currentTime = Time::AbsTime();

		static uint32_t frameCount = 0;
		static Tracking::Timestep previousTime = currentTime;

		frameCount++;
		if (currentTime.Seconds() - previousTime.Seconds() >= 1.0f)
		{
			uint32_t timeInMS = (uint32_t)(1000.0f / frameCount);
			std::string titleWithFPS = std::string(m_Title) + " [" + std::to_string(frameCount) + " FPS, " + std::to_string(timeInMS) + " ms ]";

			glfwSetWindowTitle(m_Window, titleWithFPS.c_str());

			frameCount = 0;
			previousTime = currentTime;
		}
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
}