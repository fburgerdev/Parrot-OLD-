#pragma once
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	namespace Graphics
	{
		class IndexBuffer_OPENGL : public IndexBufferAPI
		{
		public:
			IndexBuffer_OPENGL(const uint32_t* indices, uint32_t count, bool isStatic);
			~IndexBuffer_OPENGL();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void OverwriteData(const uint32_t* indices, uint32_t count, uint32_t offset = 0) override;
		private:
			uint32_t m_ID;
			bool m_IsStatic;
		};
	}
}