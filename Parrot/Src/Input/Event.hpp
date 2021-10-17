#pragma once
#include "Input.hpp"

namespace Parrot
{
	class Event
	{
	private:
		// each struct uses exactly 8 bytes so we can use all structs within a union
		struct WindowResizeEvent { Math::Vec2u dim; };
		struct MouseMoveEvent { Math::Vec2u pos; };
		struct MouseButtonEvent { Mouse::Button button; Mouse::ButtonState state; };
		struct MouseScrollEvent { int32_t xOffset; int32_t yOffset; };
		struct KeyboardEvent { Keyboard::KeyCode keyCode; Keyboard::KeyState state; };
	public:
		enum class Type : uint8_t
		{
			WindowResizeEvent, WindowCloseRequestEvent, WindowMaximizeEvent, MouseMoveEvent, MouseButtonEvent, MouseScrollEvent, KeyboardEvent, WindowGotFocus, WindowLostFocus
		};

		Type type;
		union
		{
			WindowResizeEvent windowResizeEvent;
			MouseMoveEvent mouseMoveEvent;
			MouseButtonEvent mouseButtonEvent;
			MouseScrollEvent mouseScrollEvent;
			KeyboardEvent keyboardEvent;
		};
	public:
		Event(Type type)
			: type(type), windowResizeEvent() {}
		Event(const Event& e) { type = e.type;  windowResizeEvent.dim = e.windowResizeEvent.dim; }
	};
}