#pragma once
#include "Texture.hpp"

namespace Parrot
{
	namespace GraphicsObject
	{
		class SubTexture
		{
		private:
			const Texture& m_Tex;
			Math::Vec2u m_TexOffset;
			Math::Vec2u m_TexSize;
		public:
			SubTexture(const Texture& tex, Math::Vec2u texOffset, Math::Vec2u texSize)
				: m_Tex(tex), m_TexOffset(texOffset), m_TexSize(texSize) {}
		};
	}
}