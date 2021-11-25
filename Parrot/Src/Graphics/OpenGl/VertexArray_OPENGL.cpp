#include "Ptpch.hpp"
#include "VertexArray_OPENGL.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	namespace Graphics
	{
		VertexArray_OPENGL::VertexArray_OPENGL(const VertexBufferAPI* vb, const VertexBufferLayout& layout)
		{
			glGenVertexArrays(1, &m_ID);
			Bind();
			vb->Bind();
			auto& elements = layout.GetElements();
			uint64_t offset = 0;
			for (unsigned int i = 0; i < elements.size(); ++i)
			{
				const auto& element = elements[i];
				glEnableVertexAttribArray(i);
				if (element.dType == VertexBufferElement::DType::Int32 || element.dType == VertexBufferElement::DType::Uint32)
				{
					glVertexAttribIPointer(i, element.count, (int32_t)element.dType, layout.GetStride(), (const void*)offset);
				}
				else
				{
					glVertexAttribPointer(i, element.count, (int32_t)element.dType, GL_FALSE, layout.GetStride(), (const void*)offset);
				}
				offset += element.GetStride();
			}
		}

		VertexArray_OPENGL::~VertexArray_OPENGL()
		{
			glDeleteVertexArrays(1, &m_ID);
		}

		void VertexArray_OPENGL::Bind() const
		{
			glBindVertexArray(m_ID);
		}
		void VertexArray_OPENGL::Unbind() const
		{
			glBindVertexArray(0);
		}
	}
}