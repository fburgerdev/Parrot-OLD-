#pragma once
#include "Input/Event.hpp"

namespace Parrot
{
	// defined in "Application.cpp"
	void TriggerOnEvent(const Input::Event& e);

	// defined in "Event.cpp"
	void InitKeyStrings();

	// defined in "Time.cpp"
	void StartGlobalStopwatch();
	void ResolveUpdateStopwatch();

	// defined in "Input.cpp"
	void SetMouseButtonState(Input::Mouse::MouseButton button, Input::Mouse::MouseButtonState state);
	void SetKeyboardKeyState(Input::Keyboard::Key key, Input::Keyboard::KeyState state);
}