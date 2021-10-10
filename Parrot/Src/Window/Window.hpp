#pragma once
#include "Math/Vector.hpp"

namespace Parrot
{
	class Window
	{
	public:
		// Resizes the window to the largest possible size
		// Trigggers the WindowResizeEvent!
		static void Maximize();
		// Shows the framerate in the window title
		static void ShowFrames(bool state);
		// Trigggers the WindowResizeEvent!
		static void Resize(Math::Vec2u dim);
		// Returns current size of the window
		// Format: Vec2u = (width in pixels, height in pixels
		static Math::Vec2u GetSize();
		// Sends Framebuffer to the monitor and proccesses event
		// Needs to be called regulary, otherwise the window won't reply
		static void Display();

		static void SetCursorPos(Math::Vec2i pos);
		static Math::Vec2i GetCursorPos();
	};
}