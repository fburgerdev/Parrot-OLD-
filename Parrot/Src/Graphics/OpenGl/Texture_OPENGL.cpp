#include "Ptpch.hpp"
#include "Texture_OPENGL.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	namespace Graphics
	{
		Texture_OPENGL::Texture_OPENGL(const Math::Vec4u8* buffer, const Math::Vec2u& size, const TextureAPI::Settings& settings)
			: m_ID(0)
		{
			glGenTextures(1, &m_ID);
			glBindTexture(GL_TEXTURE_2D, m_ID);
			glEnable(GL_TEXTURE_2D);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)buffer);
			if (settings.mipmap != TextureAPI::Settings::Mipmap::None)
				glGenerateMipmap(GL_TEXTURE_2D);

			int32_t minFilter;
			if (settings.mipmap == TextureAPI::Settings::Mipmap::None)
				minFilter = (int32_t)settings.minFilter;
			else if (settings.minFilter == TextureAPI::Settings::Filter::Linear && settings.mipmap == TextureAPI::Settings::Mipmap::Linear)
				minFilter = GL_LINEAR_MIPMAP_LINEAR;
			else if (settings.minFilter == TextureAPI::Settings::Filter::Linear && settings.mipmap == TextureAPI::Settings::Mipmap::Nearest)
				minFilter = GL_LINEAR_MIPMAP_NEAREST;
			else if (settings.minFilter == TextureAPI::Settings::Filter::Nearest && settings.mipmap == TextureAPI::Settings::Mipmap::Linear)
				minFilter = GL_NEAREST_MIPMAP_LINEAR;
			else
				minFilter = GL_NEAREST_MIPMAP_NEAREST;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int32_t)settings.magFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int32_t)settings.horWrap);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int32_t)settings.verWrap);
		}
		Texture_OPENGL::~Texture_OPENGL()
		{
			glDeleteTextures(1, &m_ID);
		}

		void Texture_OPENGL::Bind(uint32_t slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}
		void Texture_OPENGL::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}