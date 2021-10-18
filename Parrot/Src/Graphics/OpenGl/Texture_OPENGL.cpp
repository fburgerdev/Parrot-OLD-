#include "Ptpch.hpp"
#include "Texture_OPENGL.hpp"
#include "Vendor/stb/stb_image.h"
#include "Utils/StrFuncs.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Texture_OPENGL::Texture_OPENGL(const Utils::Filepath& filepath, const TextureAPI::Config& config)
		: m_ID(0)
	{
		// file -> buffer
		int32_t colorChannels = 4;
		if (Utils::StrIsEqual("png", filepath.Extension().data()) || Utils::StrIsEqual("jpg", filepath.Extension().data()))
			stbi_set_flip_vertically_on_load(true);
		else
			InternalLog::LogAssert(false, "Couldn't identify texture format in \"%\"! Textures currently only support \".png\", \".jpg\".", filepath.Filename());
		int32_t width, height, BPP;
		uint8_t* buffer = stbi_load(filepath.FullPath().c_str(), &width, &height, &BPP, colorChannels);
		InternalLog::LogAssert(buffer, "Texture with path \"%\" couldn't be loaded. Check if the path is correct and the file isn't corrupted.", filepath.FullPath());

		// upload buffer
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		if (config.mipmap != Config::Mipmap::None)
			glGenerateMipmap(GL_TEXTURE_2D);

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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int32_t)config.magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int32_t)config.horWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int32_t)config.verWrap);

		delete[] buffer;
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

	Math::Vec2u Texture_OPENGL::GetSize() const
	{
		return m_Size;
	}
}