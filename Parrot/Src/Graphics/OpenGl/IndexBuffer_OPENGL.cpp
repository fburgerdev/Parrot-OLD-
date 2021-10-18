#include "Ptpch.hpp"
#include "IndexBuffer_OPENGL.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	IndexBuffer_OPENGL::IndexBuffer_OPENGL(const uint32_t* indices, uint32_t count, bool isStatic)
		: m_ID(0), m_IsStatic(isStatic)
	{
		glGenBuffers(1, &m_ID);
		Bind();
		if (m_IsStatic)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		else
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);
	}
	IndexBuffer_OPENGL::~IndexBuffer_OPENGL()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void IndexBuffer_OPENGL::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
	void IndexBuffer_OPENGL::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer_OPENGL::OverwriteData(const uint32_t* indices, uint32_t count, uint32_t offset)
	{
		if (m_IsStatic)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		else
			glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(uint32_t), indices);
	}
}