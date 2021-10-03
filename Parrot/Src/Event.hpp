#pragma once
#include "Window.hpp"
#include "Input.hpp"

namespace Parrot
{
	class Event
	{
	private:
		struct WindowResizeEvent
		{
			Vector::Vec2u dim;
		};
		struct MouseMoveEvent
		{
			Vector::Vec2u pos;
		};
		struct MouseButtonEvent
		{
			Input::Mouse::MouseButton button;
			Input::Mouse::MouseButtonState action;
		};
		struct MouseScrollEvent
		{
			int32_t xOffset;
			int32_t yOffset;
		};
		struct KeyboardEvent
		{
			Input::Keyboard::Key key;
			Input::Keyboard::KeyState action;
		};
	public:
		enum class Type : uint8_t
		{
			WindowResizeEvent, WindowCloseRequestEvent, WindowMaximizeEvent, MouseMoveEvent, MouseButtonEvent, MouseScrollEvent, KeyboardEvent
		};
	public:
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
		virtual void Log() const;
	};
}