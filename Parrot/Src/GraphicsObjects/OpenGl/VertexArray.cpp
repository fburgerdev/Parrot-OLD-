#include "Ptpch.hpp"
#ifdef PT_OPENGL
	#include "GraphicsObjects/VertexArray.hpp"
	#include "GlDebug.hpp"
	#include <glad/glad.h>

	namespace Parrot
	{
		namespace GraphicsObject
		{
			void VertexArray::CreateBuffer()
			{
				GlCall(glGenVertexArrays(1, &m_ID));
			}

			void VertexArray::AddElement(uint32_t element, VertexAttribute type, uint64_t offset, uint32_t stride)
			{
				GlCall(glEnableVertexAttribArray(element));
				switch (type)
				{
				case VertexAttribute::FLOAT:
					GlCall(glVertexAttribPointer(element, 1, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
					break;
				case VertexAttribute::FLOAT2:
					GlCall(glVertexAttribPointer(element, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
					break;
				case VertexAttribute::FLOAT3:
					GlCall(glVertexAttribPointer(element, 3, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
					break;
				case VertexAttribute::FLOAT4:
					GlCall(glVertexAttribPointer(element, 4, GL_FLOAT, GL_FALSE, stride, (const void*)offset));
					break;
				case VertexAttribute::INT:
					GlCall(glVertexAttribIPointer(element, 1, GL_INT, stride, (const void*)offset));
					break;
				default:
					break;
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
	}
#endif