#include "Ptpch.hpp"
#include "VertexBuffer_OPENGL.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	VertexBuffer_OPENGL::VertexBuffer_OPENGL(const void* vertices, uint32_t size, bool isStatic)
		: m_ID(0), m_IsStatic(isStatic)
	{
		glGenBuffers(1, &m_ID);
		Bind();
		if (m_IsStatic)
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		else
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
	}
	VertexBuffer_OPENGL::~VertexBuffer_OPENGL()
	{
		glDeleteBuffers(1, &m_ID);
	}
	
	void VertexBuffer_OPENGL::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	void VertexBuffer_OPENGL::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer_OPENGL::OverwriteData(const void* vertices, uint32_t size, uint32_t offset)
	{
		if (m_IsStatic)
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		else
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
	}
}