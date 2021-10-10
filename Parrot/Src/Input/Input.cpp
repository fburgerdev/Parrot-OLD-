#include "Ptpch.hpp"
#include "Input.hpp"

namespace Parrot
{
	namespace Input
	{
		Mouse::MouseButtonState s_MouseButtons[3] = { Mouse::MouseButtonState::Released };
		Keyboard::KeyState s_Keys[350] = { Keyboard::KeyState::Released };

		Mouse::MouseButtonState Mouse::GetButtonState(Mouse::MouseButton button)
		{
			return s_MouseButtons[(uint32_t)button];
		}
		
		Keyboard::KeyState Keyboard::GetKeyState(Keyboard::Key key)
		{
			return s_Keys[(uint32_t)key];
		}
	}

	void SetMouseButtonState(Input::Mouse::MouseButton button, Input::Mouse::MouseButtonState state)
	{
		Input::s_MouseButtons[(uint32_t)button] = state;
	}
	void SetKeyboardKeyState(Input::Keyboard::Key key, Input::Keyboard::KeyState state)
	{
		Input::s_Keys[(uint32_t)key] = state;
	}
}