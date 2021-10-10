#include "Ptpch.hpp"
#ifdef PT_OPENGL
	#include "GraphicsObjects/VertexBuffer.hpp"
	#include "GlDebug.hpp"
	#include "Core/Log.hpp"
	#include <glad/glad.h>

	namespace Parrot
	{
		namespace GraphicsObject
		{
			VertexBuffer::VertexBuffer(const void* vertices, uint32_t size, bool isStatic)
				: m_IsStatic(isStatic)
			{
				GlCall(glGenBuffers(1, &m_ID));

				Bind();
				if (m_IsStatic)
				{
					GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
				}
				else
				{
					GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW));
				}
			}

			VertexBuffer::~VertexBuffer()
			{
				if (m_ID != 0)
					GlCall(glDeleteBuffers(1, &m_ID));
			}

			void VertexBuffer::Bind() const
			{
				GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
			}

			void VertexBuffer::Unbind() const
			{
				GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
			}

			void VertexBuffer::OverwriteData(const void* vertices, uint32_t size, uint32_t byteOffset)
			{
				if (m_IsStatic == true)
				{
					GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
				}
				else
				{
					GlCall(glBufferSubData(GL_ARRAY_BUFFER, byteOffset, size, vertices));
				}
			}
		}
	}
#endif
