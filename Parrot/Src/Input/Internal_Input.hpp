#pragma once
#include "Input.hpp"

namespace Parrot
{
	void Internal_SetMouseButtonState(MouseButton button, MouseButtonState state);
	void Internal_SetKeyboardKeyState(KeyCode keyCode, KeyState state);
}