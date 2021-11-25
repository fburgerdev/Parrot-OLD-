#pragma once
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	namespace Graphics
	{
		class Texture_OPENGL : public TextureAPI
		{
		public:
			Texture_OPENGL(const uint8_t* buffer, const Math::Vec2u& size, const TextureAPI::Settings& settings);
			~Texture_OPENGL();

			virtual void Bind(uint32_t slot) const override;
			virtual void Unbind() const override;
		private:
			uint32_t m_ID;
		};
	}
}