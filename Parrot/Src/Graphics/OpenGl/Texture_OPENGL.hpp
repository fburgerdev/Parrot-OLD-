#pragma once
#include "Graphics/GraphicsAPI.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	class Texture_OPENGL : public TextureAPI
	{
	public:
		Texture_OPENGL(const PtTex& ptTex);
		~Texture_OPENGL();

		virtual void Bind(uint32_t slot) const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_ID;
	};

}