#pragma once
#include "Pch.hpp"

namespace Parrot
{
	class VertexBuffer
	{
	private:
		uint32_t m_ID;
		bool m_IsStatic;
	public:
		VertexBuffer(const void* vertices, uint32_t size, bool isStatic);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }

		void OverwriteData(const void* vertices, uint32_t size, uint32_t byteOffset = 0);
	};
}