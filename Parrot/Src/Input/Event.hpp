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
		struct MouseButtonEvent { MouseButton button; MouseButtonState state; };
		struct MouseScrollEvent { int32_t xOffset; int32_t yOffset; };
		struct KeyboardEvent { KeyCode keyCode; KeyState state; };
	public:
		enum class Type : uint8_t
		{
			NoEvent = 0, WindowResizeEvent, WindowCloseRequestEvent, WindowMaximizeEvent, MouseMoveEvent, MouseButtonEvent, MouseScrollEvent, KeyboardEvent, WindowGotFocus, WindowLostFocus
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
		Event()
			: type(Type::NoEvent), windowResizeEvent() {}
		Event(Type type)
			: type(type), windowResizeEvent() {}
		Event(const Event& e) { type = e.type;  windowResizeEvent.dim = e.windowResizeEvent.dim; }
		void operator=(const Event& e) { type = e.type;  windowResizeEvent.dim = e.windowResizeEvent.dim; }
	};
}