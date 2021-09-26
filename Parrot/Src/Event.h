#pragma once
#include "Vector.h"
#include "Log.h"
#include "Key.h"
#include "Window.h"

namespace Parrot
{
	struct Window::Event
	{
		enum class Type : uint8_t
		{
			WindowResizeEvent, WindowCloseRequestEvent, WindowMaximizeEvent, MouseMoveEvent, MouseButtonEvent, KeyboardEvent
		};
		virtual Type GetType() const = 0;
		virtual void Log() const = 0;

		template<class EventType>
		const EventType& Get() const { return (const EventType&)*this;  }
	};

	struct Window::WindowResizeEvent : public Event
	{
		WindowResizeEvent(Vector::Vec2u dim)
			: dim(dim) {}

		virtual Type GetType() const override { return Type::WindowResizeEvent; }
		virtual void Log() const override { Log::LogEvent("WindowResizeEvent: width = %u, height = %u", dim.x, dim.y); }
		Vector::Vec2u dim;
	};

	struct Window::WindowCloseRequestEvent : public Event
	{
		virtual Type GetType() const override { return Type::WindowCloseRequestEvent; }
		virtual void Log() const override { Log::LogEvent("WindowCloseRequestEvent:"); }
	};

	struct Window::WindowMaximizeEvent : public Event
	{
		virtual Type GetType() const override { return Type::WindowMaximizeEvent; }
		virtual void Log() const override { Log::LogEvent("WindowMaximizeEvent:"); }
	};

	struct Window::MouseMoveEvent : public Event
	{
		MouseMoveEvent(Vector::Vec2u pos)
			: pos(pos) {}

		virtual Type GetType() const override { return Type::MouseMoveEvent; }
		virtual void Log() const override { Log::LogEvent("MouseMoveEvent: x = %u, y = %u", pos.x, pos.y); }
		Vector::Vec2u pos;
	};

	struct Window::MouseButtonEvent : public Event
	{
		Window::MouseButtonEvent(Window::Mouse::MouseButton button, Window::Mouse::MouseButtonState action)
			: button(button), action(action) {}

		static constexpr const char* s_Button[3] = { "Left", "Right", "Middle" };
		static constexpr const char* s_Action[2] = { "Release", "Press" };

		virtual Type GetType() const override { return Type::MouseButtonEvent; }
		virtual void Log() const override { Log::LogEvent("MouseButtonEvent: button = %s, action = %s", s_Button[(uint8_t)button], s_Action[(uint8_t)action]); }

		Window::Mouse::MouseButton button;
		Window::Mouse::MouseButtonState action;
	};

	struct Window::KeyboardEvent : public Event
	{
		KeyboardEvent(Keyboard::Key key, Keyboard::KeyState action)
			: key(key), action(action) {}

		static constexpr const char* s_Action[3] = { "Release", "Press", "Repeat"};

		virtual Type GetType() const override { return Type::KeyboardEvent; }
		virtual void Log() const override { Log::LogEvent("KeyboardEvent: key = '%c', action = %s", (char)key, s_Action[(uint8_t)action]); }

		Keyboard::Key key;
		Keyboard::KeyState action;
	};
}