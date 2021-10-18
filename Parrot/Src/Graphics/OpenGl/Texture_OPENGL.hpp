#pragma once
#include "Graphics/GraphicsAPI.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	class Texture_OPENGL : public TextureAPI
	{
	public:
		Texture_OPENGL(const Utils::Filepath& filepath, const TextureAPI::Config& config);
		~Texture_OPENGL();

		virtual void Bind(uint32_t slot) const override;
		virtual void Unbind() const override;

		virtual Math::Vec2u GetSize() const override;
	private:
		uint32_t m_ID;
		Math::Vec2u m_Size;
	};

}