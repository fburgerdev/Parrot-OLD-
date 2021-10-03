#include "Pch.hpp"
#include "Core.hpp"
#include "Window.hpp"
#include "Application.hpp"
#include "Event.hpp"
#include "Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Parrot
{
	void PushEvent(const Parrot::Event& e);
	void InitRenderer();

	// Mouse
	Vector::Vec2u s_MousePos;
	Input::Mouse::MouseButtonState s_MouseButtonStates[3] = { Input::Mouse::MouseButtonState::Released };

	// Keyboard
	Input::Keyboard::KeyState s_KeyStates[350] = { Input::Keyboard::KeyState::Released };

	// Window
	GLFWwindow* s_Window;
	const char* s_Title;
	Vector::Vec2u s_Dim;
	bool s_ShowFrames = true;

	// Mouse
	void Input::Mouse::SetPos(Vector::Vec2u pos)
	{
		s_MousePos = pos;
		glfwSetCursorPos(s_Window, (double)pos.x, (double)pos.y);
	}

	Vector::Vec2u Input::Mouse::GetPos()
	{
		return s_MousePos;
	}

	Input::Mouse::MouseButtonState Input::Mouse::GetButtonState(MouseButton button)
	{
		return s_MouseButtonStates[(uint8_t)button];
	}
	
	// Keyboard
	Input::Keyboard::KeyState Input::Keyboard::GetKeyState(Key key)
	{
		return s_KeyStates[(int32_t)key];
	}

	// Window
	static void UpdateTitleFrames()
	{
		double currentTime = glfwGetTime();

		static uint32_t frameCount = 0;
		static double previousTime = currentTime;

		frameCount++;
		if (currentTime - previousTime >= 1.0)
		{
			std::string titleWithFPS = std::string(s_Title) + " [" + std::to_string(frameCount) + " FPS, " + std::to_string(1000.0f / frameCount) + " ms ]";

			glfwSetWindowTitle(s_Window, titleWithFPS.c_str());

			frameCount = 0;
			previousTime = currentTime;
		}
	}

	Application::Application(const char* title, Vector::Vec2u dim, const Window::Config& config)
	{
		// GLFW
		if (glfwInit() == GL_FALSE)
			Parrot::Log::LogError("Failed to initialize GLFW!");
		else 
			Log::LogInfo("GLFW initialized successfully!");

		// Window creation
		glfwWindowHint(GLFW_RESIZABLE, config.resizable);
		if (config.fullscreen)
			s_Window = glfwCreateWindow(dim.x, dim.y, title, glfwGetPrimaryMonitor(), NULL);
		else
			s_Window = glfwCreateWindow(dim.x, dim.y, title, NULL, NULL);
		Log::LogInfo("Window created successfully! title = \"%s\", windowDim = Vec2u(% u, % u)", title, dim.x, dim.y);
		glfwMakeContextCurrent(s_Window);
		if (config.maximized)
			glfwMaximizeWindow(s_Window);

		// GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Parrot::Log::LogError("Failed to initialize GLAD!");
		else 
			Parrot::Log::LogInfo("GLAD initialized successfully!");
		InitRenderer();

		// Data assignment
		s_Title = title;
		s_Dim = dim;

		// Callbacks
		glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				glViewport(0, 0, width, height);
				Event e(Event::Type::WindowResizeEvent);
				s_Dim = Vector::Vec2u((uint32_t)width, (uint32_t)height);
				e.windowResizeEvent.dim = Vector::Vec2u((uint32_t)width, (uint32_t)height);
				PushEvent(e);
			});
		glfwSetWindowMaximizeCallback(s_Window, [](GLFWwindow* window, int32_t state)
			{
				if (state == GLFW_PRESS)
				{
					Event e(Event::Type::WindowMaximizeEvent);
					PushEvent(e);
				}
			});
		glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window)
			{
				Event e(Event::Type::WindowCloseRequestEvent);
				PushEvent(e);
			});
		glfwSetCursorPosCallback(s_Window, [](GLFWwindow* window, double x, double y)
			{
				Event e(Event::Type::MouseMoveEvent);
				e.mouseMoveEvent.pos = Vector::Vec2u((uint32_t)x, (uint32_t)y);
				PushEvent(e);
			});
		glfwSetMouseButtonCallback(s_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
			{
				Event e(Event::Type::MouseButtonEvent);
				e.mouseButtonEvent.button = (Input::Mouse::MouseButton)button;
				e.mouseButtonEvent.action = (Input::Mouse::MouseButtonState)action;
				s_MouseButtonStates[button] = (Input::Mouse::MouseButtonState)action;
				PushEvent(e);
			});
		glfwSetScrollCallback(s_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Event e(Event::Type::MouseScrollEvent);
				e.mouseScrollEvent.xOffset = (int32_t)xOffset;
				e.mouseScrollEvent.yOffset = (int32_t)yOffset;
				PushEvent(e);
			});
		glfwSetKeyCallback(s_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				Event e(Event::Type::KeyboardEvent);
				e.keyboardEvent.key = (Input::Keyboard::Key) key;
				e.keyboardEvent.action = (Input::Keyboard::KeyState)action;
				s_KeyStates[key] = (Input::Keyboard::KeyState)action;
				PushEvent(e);
			});
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

	void Window::VSync(bool state)
	{
		glfwSwapInterval((int32_t)state);
	}

	void Window::Maximized(bool state)
	{
		if (state == true)
			glfwMaximizeWindow(s_Window);
		else
			glfwRestoreWindow(s_Window);
	}

	void Window::ShowFrames(bool state)
	{
		s_ShowFrames = state;
	}

	void Window::Resize(Vector::Vec2u dim)
	{
		glfwSetWindowSize(s_Window, (int32_t)dim.x, (int32_t)dim.y);
		s_Dim = dim;
	}

	Vector::Vec2u Window::GetDim()
	{
		return s_Dim;
	}

	void DisplayWindow()
	{
		if (s_ShowFrames)
			UpdateTitleFrames();
		glfwSwapBuffers(s_Window);
		glfwPollEvents();
	}

	Application::~Application()
	{
		glfwTerminate();
		Log::LogInfo("Window destroyed successfully!");
	}

	void Window::ClearColorBuffer(Vector::Vec4f clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glad_glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::ClearDepthBuffer()
	{
		glad_glClear(GL_DEPTH_BUFFER_BIT);
	}
}
