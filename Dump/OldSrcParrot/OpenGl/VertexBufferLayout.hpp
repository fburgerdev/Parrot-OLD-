#pragma once
#include "Pch.hpp"
#include "GlDebug.hpp"

namespace Parrot
{
	struct VertexBuffferElement
	{
		uint32_t type;
		uint32_t count;
		int32_t normalized;

		uint32_t GetStride() const
		{
			switch (type)
			{
			case GL_FLOAT: return 4 * count;
			case GL_UNSIGNED_INT: return 4 * count;
			case GL_INT: return 4 * count;
			case GL_UNSIGNED_BYTE: return 1 * count;
			}
			assert(false);
			return 0;
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBuffferElement> m_Elements;
		uint32_t m_Stride;
	public:
		VertexBufferLayout() : m_Stride(0) {}

		template<typename T>
		void Push(uint32_t count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(uint32_t count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * 4;
		}

		template<>
		void Push<int>(uint32_t count)
		{
			m_Elements.push_back({ GL_INT, count, GL_FALSE });
			m_Stride += count * 4;
		}

		template<>
		void Push<uint32_t>(uint32_t count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * 4;
		}

		template<>
		void Push<uint8_t>(uint32_t count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
			m_Stride += count * 1;
		}

		const std::vector<VertexBuffferElement>& GetElements() const { return m_Elements; }
		inline uint32_t  GetStride() const { return m_Stride; }
	};
}