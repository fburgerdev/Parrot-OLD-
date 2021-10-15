#include "Ptpch.hpp"
#include "Input.hpp"

namespace Parrot
{
	static Mouse::ButtonState s_MouseButtons[3] = { Mouse::ButtonState::Released };
	static Keyboard::KeyState s_Keys[350] = { Keyboard::KeyState::Released };

	Mouse::ButtonState Mouse::GetButtonState(Mouse::Button button)
	{
		return s_MouseButtons[(uint32_t)button];
	}
		
	Keyboard::KeyState Keyboard::GetKeyState(Keyboard::KeyCode key)
	{
		return s_Keys[(uint32_t)key];
	}

	void SetMouseButtonState(Mouse::Button button, Mouse::ButtonState state)
	{
		s_MouseButtons[(uint32_t)button] = state;
	}
	void SetKeyboardKeyState(Keyboard::KeyCode keyCode, Keyboard::KeyState state)
	{
		s_Keys[(uint32_t)keyCode] = state;
	}
}