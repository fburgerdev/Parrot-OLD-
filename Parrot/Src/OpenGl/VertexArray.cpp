#include "Pch.hpp"
#include "VertexArray.hpp"
#include "GlDebug.hpp"
#include "Core.hpp"
#include <glad/glad.h>

namespace Parrot
{
	VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		GlCall(glGenVertexArrays(1, &m_ID));
		vb.Bind();
		Bind();
		auto& elements = layout.GetElements();
		uint64_t offset = 0;
		for (uint32_t i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GlCall(glEnableVertexAttribArray(i));
			if (element.type == GL_INT || element.type == GL_UNSIGNED_INT)
			{
				GlCall(glVertexAttribIPointer(i, element.count, element.type, layout.GetStride(), (const void*)offset));
			}
			else
			{
				GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			}
			offset += element.GetStride();;
		}
	}

	VertexArray::~VertexArray()
	{
		if (m_ID != 0)
			GlCall(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::Bind() const
	{
		GlCall(glBindVertexArray(m_ID));
	}

	void VertexArray::Unbind() const
	{
		GlCall(glBindVertexArray(0));
	}
}