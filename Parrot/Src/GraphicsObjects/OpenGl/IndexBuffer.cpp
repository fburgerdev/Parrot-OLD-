#include "Ptpch.hpp"
#ifdef PT_OPENGL
	#include "GraphicsObjects/IndexBuffer.hpp"
	#include "GlDebug.hpp"
	#include "Core/Macros.hpp"
	#include <glad/glad.h>

	namespace Parrot
	{
		namespace GraphicsObject
		{
			IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count, bool isStatic)
				: m_IsStatic(isStatic)
			{
				GlCall(glGenBuffers(1, &m_ID));
				Bind();
				if (m_IsStatic)
				{
					GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
				}
				else
				{
					GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW));
				}
			}

			IndexBuffer::~IndexBuffer()
			{
				if (m_ID != 0)
					GlCall(glDeleteBuffers(1, &m_ID));
			}

			void IndexBuffer::Bind() const
			{
				GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
			}

			void IndexBuffer::Unbind() const
			{
				GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			}

			void IndexBuffer::OverwriteData(const void* indices, uint32_t count, uint32_t byteOffset)
			{
				if (m_IsStatic)
				{
					GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
				}
				else
				{
					GlCall(glBufferSubData(GL_ARRAY_BUFFER, byteOffset, count * sizeof(unsigned int), indices));
				}
			}
		}
	}
#endif