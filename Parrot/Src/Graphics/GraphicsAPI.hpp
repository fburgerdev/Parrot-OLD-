#pragma once
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Utils/Filepath.hpp"
#include "VertexBufferLayout.hpp"

namespace Parrot
{
	namespace Graphics
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

			virtual void OverwriteData(const void* vertices, size_t size, size_t offset = 0) = 0;
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
			struct Settings
			{
				enum class Wrap : int32_t
				{
					ClampToEdge = 0x812F, ClampToBorder = 0x812D, Repeat = 0x2901, MirroredRepeat = 0x8370
				};
				enum class Filter : int32_t
				{
					Linear = 0x2601, Nearest = 0x2600
				};
				enum class Mipmap : uint8_t
				{
					None, Linear, Nearest
				};
				Wrap horWrap = Wrap::ClampToEdge;
				Wrap verWrap = Wrap::ClampToEdge;
				Filter magFilter = Filter::Linear;
				Filter minFilter = Filter::Linear;
				Mipmap mipmap = Mipmap::None;
			};
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

			virtual void SetUniformInt(const std::string& identifier, int32_t val) const = 0;
			virtual void SetUniformVec2i(const std::string& identifier, const Math::Vec2i& val) const = 0;
			virtual void SetUniformVec3i(const std::string& identifier, const Math::Vec3i& val) const = 0;
			virtual void SetUniformVec4i(const std::string& identifier, const Math::Vec4i& val) const = 0;

			virtual void SetUniformFloat(const std::string& identifier, float val) const = 0;
			virtual void SetUniformVec2f(const std::string& identifier, const Math::Vec2f& val) const = 0;
			virtual void SetUniformVec3f(const std::string& identifier, const Math::Vec3f& val) const = 0;
			virtual void SetUniformVec4f(const std::string& identifier, const Math::Vec4f& val) const = 0;

			virtual void SetUniformMat2f(const std::string& identifier, const Math::Mat2f& mat) const = 0;
			virtual void SetUniformMat3f(const std::string& identifier, const Math::Mat3f& mat) const = 0;
			virtual void SetUniformMat4f(const std::string& identifier, const Math::Mat4f& mat) const = 0;
		};

		IndexBufferAPI* CreateIndexBufferAPI(const uint32_t* indices, uint32_t count, bool isStatic = false);
		VertexBufferAPI* CreateVertexBufferAPI(const void* vertices, size_t size, bool isStatic = false);
		VertexArrayAPI* CreateVertexArrayAPI(const VertexBufferAPI* vb, const VertexBufferLayout& layout);
		TextureAPI* CreateTextureAPI(const Math::Vec4u8* buffer, Math::Vec2u size, const TextureAPI::Settings& settings);
		ShaderAPI* CreateShaderAPI(const std::string& vertexSrc, const std::string& fragmentSrc);
	}
}