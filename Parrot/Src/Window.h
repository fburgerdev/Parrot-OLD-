#pragma once
#include "Vector.h"

namespace Parrot
{
	class Window
	{
	public:
		struct Config
		{
			bool resizable;
			bool maximized;
		};

		struct Mouse
		{
			enum class MouseButton : uint8_t
			{
				Left = 0, Right, Middle
			};

			enum class MouseButtonState : uint8_t
			{
				Released = 0, Pressed
			};

			static void SetPos(Vector::Vec2u pos);
			static Vector::Vec2u GetPos();

			static MouseButtonState GetButtonState(MouseButton button);
		};

		struct Keyboard
		{
			enum class Key;
			enum class KeyState : uint8_t
			{
				Released = 0, Pressed, Repeated
			};

			static KeyState GetState(Key key);
		};

		struct Event;
		struct WindowResizeEvent;
		struct WindowCloseRequestEvent;
		struct WindowMaximizeEvent;
		struct MouseMoveEvent;
		struct MouseButtonEvent;
		struct KeyboardEvent;
	private:
		static constexpr Config defaultConfig = { true, false };
	public:
		static void Create(const char* title, Vector::Vec2u dim, const Config& config = defaultConfig);
		static void VSync(bool state);
		static void Maximized(bool state);
		static void ShowFrames(bool state);
		static void Resize(Vector::Vec2u dim);
		static void Display();
		static void ClearColorBuffer(Vector::Vec4f clearColor);
		static void ClearDepthBuffer();
		static void Terminate();
	};
}

