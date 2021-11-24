#pragma once
#include "Input.hpp"

namespace Parrot
{
	enum class EventType : uint8_t
	{
		None = 0, WindowResize, CloseRequest, WindowMaximize, MouseMove, MousePress, MouseScroll, KeyPress, WindowGotFocus, WindowLostFocus, Custom
	};
	class Event
	{
	private:
		// each struct uses exactly 8 bytes so we can use all structs within a union
		struct Custom { uint64_t code; };
		struct WindowResize { Math::Vec2u dim; };
		struct MouseMove { Math::Vec2u pos; };
		struct MousePress { MouseButton button; MouseButtonState state; };
		struct MouseScroll { int32_t xOffset; int32_t yOffset; };
		struct KeyPress { KeyCode keyCode; KeyState state; };
	public:
		EventType type;
		union
		{
			Custom custom;
			WindowResize windowResize;
			MouseMove mouseMove;
			MousePress mousePress;
			MouseScroll mouseScroll;
			KeyPress keyPress;
		};
	public:
		Event()
			: type(EventType::None), custom() {}
		Event(EventType type)
			: type(type), custom() {}
		Event(EventType type, uint64_t code)
			: type(type) { custom.code = code; }
		Event(EventType type, Math::Vec2u vec)
			: type(type) { windowResize.dim = vec; }
		Event(EventType type, MouseButton button, MouseButtonState state = MouseButtonState::Pressed)
			: type(type) { mousePress.button = button; mousePress.state = state; }
		Event(EventType type, int32_t xOffset, int32_t yOffset)
			: type(type) { mouseScroll.xOffset = xOffset; mouseScroll.yOffset = yOffset; }
		Event(EventType type, KeyCode keyCode, KeyState state = KeyState::Pressed)
			: type(type) { keyPress.keyCode = keyCode; keyPress.state = state; }
		Event(const Event& e) { type = e.type; custom = e.custom; }
		void operator=(const Event& e) { type = e.type; custom = e.custom;; }
	};
}