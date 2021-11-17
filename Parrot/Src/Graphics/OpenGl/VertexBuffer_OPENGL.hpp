#pragma once
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	class VertexBuffer_OPENGL : public VertexBufferAPI
	{
	public:
		VertexBuffer_OPENGL(const void* vertices, size_t size, bool isStatic);
		~VertexBuffer_OPENGL();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void OverwriteData(const void* vertices, size_t size, size_t offset = 0) override;
	private:
		uint32_t m_ID = 0;
		bool m_IsStatic;
	};
}