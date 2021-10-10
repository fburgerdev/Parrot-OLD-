#pragma once
#include "Math/Vector.hpp"

namespace Parrot
{
	class WindowAPI
	{
	public:
		class Config
		{
		public:
			bool fullscreen = false;
			bool maximized = false;
			bool resizable = true;
		};

		virtual void Maximize() = 0;
		virtual void ShowFrames(bool state) = 0;
		virtual void Resize(Math::Vec2u dim) = 0;
		virtual Math::Vec2u GetSize() = 0;
		virtual void Display() = 0;

		virtual void SetCursorPos(Math::Vec2i pos) = 0;
		virtual Math::Vec2i GetCursorPos() = 0;
	public:
		// Window that gets created on default when the client application starts.
		static WindowAPI* s_DefaultWindow;

		// Standard window configuration
		static constexpr Config c_DefaultConfig = { false, false, true };
		static WindowAPI* Create(const char* title, Math::Vec2u dim, const WindowAPI::Config& config = c_DefaultConfig);

		// Handles different contexts of Window
		static void SetContext(WindowAPI* window);
		static WindowAPI* GetContext();
	};
}