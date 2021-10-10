#pragma once
#include "Ptpch.hpp"
#include "Input.hpp"

namespace Parrot
{
	namespace Input
	{
		class Event
		{
		private:
			struct WindowResizeEvent
			{
				Math::Vec2u dim;
			};
			struct MouseMoveEvent
			{
				Math::Vec2u diff;
			};
			struct MouseButtonEvent
			{
				Input::Mouse::MouseButton button;
				Input::Mouse::MouseButtonState state;
			};
			struct MouseScrollEvent
			{
				int32_t xOffset;
				int32_t yOffset;
			};
			struct KeyboardEvent
			{
				Input::Keyboard::Key key;
				Input::Keyboard::KeyState state;
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
			// Logs the event via an ".LogEvent" call
			virtual void Log() const;
		};
	}
}