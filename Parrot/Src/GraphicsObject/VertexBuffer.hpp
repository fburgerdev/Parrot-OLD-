#pragma once
#include "Ptpch.hpp"

namespace Parrot
{
	namespace GraphicsObject
	{
		class VertexBuffer
		{
		private:
			uint32_t m_ID = 0;
		public:
			uint32_t GetID() const { return m_ID; }
		private:
			bool m_IsStatic;
		public:
			VertexBuffer(const void* vertices, uint32_t size, bool isStatic);
			~VertexBuffer();

			void Bind() const;
			void Unbind() const;

			void OverwriteData(const void* vertices, uint32_t size, uint32_t byteOffset = 0);
		};
	}
}