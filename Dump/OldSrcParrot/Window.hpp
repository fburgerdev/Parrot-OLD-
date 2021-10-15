#pragma once
#include "Vector.hpp"

namespace Parrot
{
	namespace Window
	{
		class Config
		{
		public:
			bool fullscreen = false;
			bool maximized = false;
			bool resizable = true;
		};
		constexpr Config c_DefaultConfig = { false, false, true };
	
		void VSync(bool state);
		void Maximized(bool state);
		void ShowFrames(bool state);
		void Resize(Vector::Vec2u dim);
		Vector::Vec2u GetDim();
		void ClearColorBuffer(Vector::Vec4f clearColor);
		void ClearDepthBuffer();
	}
}

