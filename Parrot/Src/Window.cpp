#include "Window.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include "Event.h"
#include <string>

#define IS_WINDOW_OPEN_CHECK if (!s_IsOpen) { Log::LogError("Window was not created!"); Application::Terminate(); return; }

void PushEvent(const Parrot::Window::Event& e);
namespace Parrot
{
	// Mouse
	Vector::Vec2u s_MousePos;
	Window::Mouse::MouseButtonState s_MouseButtonStates[3] = { Window::Mouse::MouseButtonState::Released };

	// Keyboard
	Window::Keyboard::KeyState s_KeyStates[350] = { Window::Keyboard::KeyState::Released };

	// Window
	GLFWwindow* s_Window;
	const char* s_Title;
	Vector::Vec2u s_Dim;
	bool s_ShowFrames = true;
	bool s_IsOpen = false;
	
	// Mouse
	void Window::Mouse::SetPos(Vector::Vec2u pos)
	{
		IS_WINDOW_OPEN_CHECK
		s_MousePos = pos;
		glfwSetCursorPos(s_Window, (double)pos.x, (double)pos.y);
	}

	Vector::Vec2u Window::Mouse::GetPos()
	{
		return s_MousePos;
	}

	Window::Mouse::MouseButtonState Window::Mouse::GetButtonState(MouseButton button)
	{
		return s_MouseButtonStates[(uint8_t)button];
	}
	
	// Keyboard
	Window::Keyboard::KeyState Window::Keyboard::GetState(Key key)
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
			std::string titleWithFPS = std::string(s_Title) + " [" + std::to_string(frameCount) + " FPS]";

			glfwSetWindowTitle(s_Window, titleWithFPS.c_str());

			frameCount = 0;
			previousTime = currentTime;
		}
	}

	void Window::Create(const char* title, Vector::Vec2u dim, const Config& config)
	{
		if (s_IsOpen)
		{
			Log::LogWarning("Window was already created!");
			return;
		}
		
		glfwInit();
		Log::LogInfo("GLFW initialized successfully!");
		glfwWindowHint(GLFW_RESIZABLE, config.resizable);
		s_Window = glfwCreateWindow(dim.x, dim.y, title, NULL, NULL);
		Log::LogInfo("Window created! Title = \"%s\", WindowDim = Vec2u(% u, % u)", title, dim.x, dim.y);
		glfwMakeContextCurrent(s_Window);
		if (config.maximized)
			glfwMaximizeWindow(s_Window);
	
		s_Title = title;
		s_Dim = dim;
		s_IsOpen = true;
		// Callbacks
		glfwSetWindowSizeCallback(s_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				PushEvent(WindowResizeEvent(Vector::Vec2u((uint32_t)width, (uint32_t)height)));
			});
		glfwSetWindowCloseCallback(s_Window, [](GLFWwindow* window)
			{
				PushEvent(WindowCloseRequestEvent());
			});
		glfwSetWindowMaximizeCallback(s_Window, [](GLFWwindow* window, int32_t state)
			{
				if (state == GLFW_PRESS)
					PushEvent(WindowMaximizeEvent());
			});
		glfwSetCursorPosCallback(s_Window, [](GLFWwindow* window, double x, double y)
			{
				s_MousePos = Vector::Vec2u((uint32_t)x, (uint32_t)y);
				PushEvent(MouseMoveEvent(Vector::Vec2u((uint32_t)x, (uint32_t)y)));
			});
		glfwSetMouseButtonCallback(s_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t scanfield)
			{
				s_MouseButtonStates[button] = (Mouse::MouseButtonState)action;
				PushEvent(MouseButtonEvent((Mouse::MouseButton)button, (Mouse::MouseButtonState)action));
			});
		
		glfwSetKeyCallback(s_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				s_KeyStates[key] = (Keyboard::KeyState)action;
				PushEvent(KeyboardEvent((Keyboard::Key)key, (Keyboard::KeyState)action));
			});
	}

	void Window::VSync(bool state)
	{
		IS_WINDOW_OPEN_CHECK
		glfwSwapInterval((int32_t)state);
	}

	void Window::Maximized(bool state)
	{
		IS_WINDOW_OPEN_CHECK
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
		IS_WINDOW_OPEN_CHECK
		glfwSetWindowSize(s_Window, (int32_t)dim.x, (int32_t)dim.y);
		s_Dim = dim;
	}

	void Window::Display()
	{
		IS_WINDOW_OPEN_CHECK
		if (s_ShowFrames)
			UpdateTitleFrames();
		glfwSwapBuffers(s_Window);
		glfwPollEvents();
	}

	void Window::ClearColorBuffer(Vector::Vec4f clearColor)
	{
		IS_WINDOW_OPEN_CHECK
	}

	void Window::ClearDepthBuffer()
	{
		IS_WINDOW_OPEN_CHECK
	}

	void Window::Terminate()
	{
		if (!s_IsOpen)
		{
			Log::LogWarning("No Window to destroy!");
			return;
		}
		glfwTerminate();
		Log::LogInfo("Window destroyed succesfully!");
		s_IsOpen = false;
	}
}
