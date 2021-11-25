#pragma once
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	namespace Graphics
	{
		class VertexArray_OPENGL : public VertexArrayAPI
		{
		public:
			VertexArray_OPENGL(const VertexBufferAPI* vb, const VertexBufferLayout& layout);
			~VertexArray_OPENGL();

			virtual void Bind() const override;
			virtual void Unbind() const override;
		private:
			uint32_t m_ID;
		};
	}
}