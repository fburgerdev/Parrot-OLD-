#pragma once
#include "Math/Vector.hpp"

namespace Parrot
{
	class IndexBufferAPI
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void OverwriteData(uint32_t* indices, uint32_t count, uint32_t offset = 0) const = 0;
		virtual void Resize(uint32_t newSize) const = 0;

		virtual void Static(bool state) = 0;
	};

	class VertexBufferAPI
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void OverwriteData(void* indices, uint32_t size, uint32_t offset = 0) const = 0;
		virtual void Resize(uint32_t newSize) const = 0;

		virtual void Static(bool state) = 0;
	};

	class ShaderAPI
	{
	public:
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
}