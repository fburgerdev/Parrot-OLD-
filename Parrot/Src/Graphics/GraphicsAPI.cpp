#include "Ptpch.hpp"
#include "GraphicsAPI.hpp"

#include "OpenGl/IndexBuffer_OPENGL.hpp"
#include "OpenGl/VertexBuffer_OPENGL.hpp"
#include "OpenGl/VertexArray_OPENGL.hpp"
#include "OpenGl/Texture_OPENGL.hpp"
#include "OpenGl/Shader_OPENGL.hpp"

namespace Parrot
{
#ifdef PT_OPENGL
	namespace Graphics
	{
		IndexBufferAPI* CreateIndexBufferAPI(const uint32_t* indices, uint32_t count, bool isStatic)
		{
			return new IndexBuffer_OPENGL(indices, count, isStatic);
		}
		VertexBufferAPI* CreateVertexBufferAPI(const void* vertices, size_t size, bool isStatic)
		{
			return new VertexBuffer_OPENGL(vertices, size, isStatic);
		}
		VertexArrayAPI* CreateVertexArrayAPI(const VertexBufferAPI* vb, const VertexBufferLayout& layout)
		{
			return new VertexArray_OPENGL(vb, layout);
		}
		TextureAPI* CreateTextureAPI(const uint8_t* buffer, Math::Vec2u size, const TextureAPI::Settings& settings)
		{
			return new Texture_OPENGL(buffer, size, settings);
		}
		ShaderAPI* CreateShaderAPI(const std::string& vertexSrc, const std::string& fragmentSrc)
		{
			return new Shader_OPENGL(vertexSrc, fragmentSrc);
		}
	}
#endif // PT_OPENGL
}
