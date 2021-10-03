#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Parrot
{
	class VertexArray
	{
	private:
		uint32_t m_ID;
	public:
		VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }
	};
}