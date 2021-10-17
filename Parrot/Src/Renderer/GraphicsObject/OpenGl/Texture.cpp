#include "Ptpch.hpp"
#ifdef PT_OPENGL
	#include "Renderer/GraphicsObject/Texture.hpp"
	#include "GlDebug.hpp"
	#include "stb/stb_image.h"
	#include "Utils/StrFuncs.hpp"

	namespace Parrot
	{
		namespace GraphicsObject
		{
			const Texture::Config Texture::s_DefaultConfig;

			Texture::Texture(const std::string& path, const Config& config)
			{
				LoadTextureFromPath(path, config);
			}

			Texture::Texture(const uint8_t* buffer, Math::Vec2u dim, ColorFormat colorFormat, const Config& config)
			{
				LoadTexture(buffer, dim, colorFormat, config);
			}

			bool Texture::LoadTextureFromPath(const std::string& path, const Config& config)
			{
				const char* extension = Utils::ExtensionFromPath(path.c_str());
				if (Utils::StrIsEqual(extension, "png") || Utils::StrIsEqual(extension, "jpg"))
					stbi_set_flip_vertically_on_load(true);
				else
				{
					Parrot::Log::LogWarning("Doesn't recognize file extension in \"%\"", Utils::FilenameFromPath(path.c_str()));
					stbi_set_flip_vertically_on_load(false);
				}
				int32_t width, height, BPP;
				uint8_t* buffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);
				if (buffer == nullptr)
				{
					Log::LogError("Texture \"%\" could not be loaded!", path.c_str());
					return false;
				}
				m_Dim = Math::Vec2u((uint32_t)width, (uint32_t)height);
				LoadTexture(buffer, m_Dim, ColorFormat::RGBA, config);
				stbi_image_free(buffer);
				return true;
			}

			void Texture::LoadTexture(const uint8_t* buffer, Math::Vec2u dim, ColorFormat colorFormat, const Config& config)
			{
				if (m_ID != 0)
					GlCall(glDeleteTextures(1, &m_ID));

				m_Dim = dim;
				GlCall(glGenTextures(1, &m_ID));
				GlCall(glBindTexture(GL_TEXTURE_2D, m_ID));
				glEnable(GL_TEXTURE_2D);
				GlCall(glTexImage2D(GL_TEXTURE_2D, 0, (int32_t)colorFormat, dim.x, dim.y, 0, (int32_t)colorFormat, GL_UNSIGNED_BYTE, buffer));
				if (config.mipmap != Config::Mipmap::None)
					GlCall(glGenerateMipmap(GL_TEXTURE_2D));

				int32_t minFilter;
				if (config.mipmap == Config::Mipmap::None)
					minFilter = (int32_t)config.minFilter;
				else if (config.minFilter == Config::Filter::Linear && config.mipmap == Config::Mipmap::Linear)
					minFilter = GL_LINEAR_MIPMAP_LINEAR;
				else if (config.minFilter == Config::Filter::Linear && config.mipmap == Config::Mipmap::Nearest)
					minFilter = GL_LINEAR_MIPMAP_NEAREST;
				else if (config.minFilter == Config::Filter::Nearest && config.mipmap == Config::Mipmap::Linear)
					minFilter = GL_NEAREST_MIPMAP_LINEAR;
				else
					minFilter = GL_NEAREST_MIPMAP_NEAREST;

				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int32_t)config.magFilter));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int32_t)config.horWrap));
				GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int32_t)config.verWrap));
			}

			Texture::~Texture()
			{
				GlCall(glDeleteTextures(1, &m_ID));
			}

			void Texture::Bind(uint32_t slot) const
			{
				Log::LogAssert(m_ID != 0, "Could not bind Texture!");
				GlCall(glActiveTexture(GL_TEXTURE0 + slot));
				GlCall(glBindTexture(GL_TEXTURE_2D, m_ID));
			}

			void Texture::Unbind() const
			{
				GlCall(glBindTexture(GL_TEXTURE_2D, 0));
			}
		}
	}
#endif