#pragma once
#include "Math/Vector.hpp"
#include "Utils/Filepath.hpp"
#include "VertexBufferLayout.hpp"
#include "Assets/Formats/PtTex.hpp"
#include "Assets/Formats/PtShader.hpp"

namespace Parrot
{
	class IndexBufferAPI
	{
	public:
		virtual ~IndexBufferAPI() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void OverwriteData(const uint32_t* indices, uint32_t count, uint32_t offset = 0) = 0;
	};

	class VertexBufferAPI
	{
	public:
		virtual ~VertexBufferAPI() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void OverwriteData(const void* vertices, uint32_t size, uint32_t offset = 0) = 0;
	};

	class VertexArrayAPI
	{
	public:
		virtual ~VertexArrayAPI() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	class TextureAPI
	{
	public:
		virtual ~TextureAPI() {};

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind() const = 0;
	};

	class ShaderAPI
	{
	public:
		virtual ~ShaderAPI() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void SetUniformInt(const std::string& identifier, int32_t val) = 0;
		virtual void SetUniformVec2i(const std::string& identifier, Math::Vec2i val) = 0;
		virtual void SetUniformVec3i(const std::string& identifier, Math::Vec3i val) = 0;
		virtual void SetUniformVec4i(const std::string& identifier, Math::Vec4i val) = 0;
		
		virtual void SetUniformFloat(const std::string& identifier, float val) = 0;
		virtual void SetUniformVec2f(const std::string& identifier, Math::Vec2f val) = 0;
		virtual void SetUniformVec3f(const std::string& identifier, Math::Vec3f val) = 0;
		virtual void SetUniformVec4f(const std::string& identifier, Math::Vec4f val) = 0;
	};

	IndexBufferAPI* CreateIndexBufferAPI(const uint32_t* indices, uint32_t count, bool isStatic = false);
	VertexBufferAPI* CreateVertexBufferAPI(const void* vertices, uint32_t size, bool isStatic = false);
	VertexArrayAPI* CreateVertexArrayAPI(const VertexBufferAPI* vb, const VertexBufferLayout& layout);
	TextureAPI* CreateTextureAPI(const PtTex& ptTex);
	ShaderAPI* CreateShaderAPI(const PtShader& ptShader);
}