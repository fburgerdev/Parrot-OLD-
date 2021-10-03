#pragma once
#include "Pch.hpp"

namespace Parrot
{
	class IndexBuffer
	{
	private:
		uint32_t m_ID;
		bool m_IsStatic;
	public:
		IndexBuffer(const uint32_t* indices, uint32_t count, bool isStatic);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }

		void OverwriteData(const void* indices, uint32_t count, uint32_t byteOffset = 0);
	};
}