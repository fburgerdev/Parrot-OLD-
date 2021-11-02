#include "Ptpch.hpp"
#include "Texture_OPENGL.hpp"

namespace Parrot
{
	Texture_OPENGL::Texture_OPENGL(const PtTex& ptTex)
		: m_ID(0)
	{
		const PtTex::Settings& settings = ptTex.GetData().settings;

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glEnable(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ptTex.GetData().size.x, ptTex.GetData().size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptTex.GetData().buffer);
		if (settings.mipmap != PtTex::Settings::Mipmap::None)
			glGenerateMipmap(GL_TEXTURE_2D);

		int32_t minFilter;
		if (settings.mipmap == PtTex::Settings::Mipmap::None)
			minFilter = (int32_t)settings.minFilter;
		else if (settings.minFilter == PtTex::Settings::Filter::Linear && settings.mipmap == PtTex::Settings::Mipmap::Linear)
			minFilter = GL_LINEAR_MIPMAP_LINEAR;
		else if (settings.minFilter == PtTex::Settings::Filter::Linear && settings.mipmap == PtTex::Settings::Mipmap::Nearest)
			minFilter = GL_LINEAR_MIPMAP_NEAREST;
		else if (settings.minFilter == PtTex::Settings::Filter::Nearest && settings.mipmap == PtTex::Settings::Mipmap::Linear)
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