#pragma once
#include "Graphics/GraphicsAPI.hpp"
#include <unordered_map>

namespace Parrot
{
	namespace Graphics
	{
		class Shader_OPENGL : public ShaderAPI
		{
		public:
			Shader_OPENGL(const std::string& vertexSrc, const std::string& fragmentSrc);
			~Shader_OPENGL();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual void SetUniformInt(const std::string& identifier, int32_t val) const override;
			virtual void SetUniformVec2i(const std::string& identifier, const Math::Vec2i& val) const override;
			virtual void SetUniformVec3i(const std::string& identifier, const Math::Vec3i& val) const override;
			virtual void SetUniformVec4i(const std::string& identifier, const Math::Vec4i& val) const override;

			virtual void SetUniformFloat(const std::string& identifier, float val) const override;
			virtual void SetUniformVec2f(const std::string& identifier, const Math::Vec2f& val) const override;
			virtual void SetUniformVec3f(const std::string& identifier, const Math::Vec3f& val) const override;
			virtual void SetUniformVec4f(const std::string& identifier, const Math::Vec4f& val) const override;

			virtual void SetUniformMat2f(const std::string& identifier, const Math::Mat2f& mat) const override;
			virtual void SetUniformMat3f(const std::string& identifier, const Math::Mat3f& mat) const override;
			virtual void SetUniformMat4f(const std::string& identifier, const Math::Mat4f& mat) const override;
		private:
			uint32_t CompileShader(int32_t shaderType, const std::string& source);
			uint32_t GetUniformLocation(const std::string& identifier) const;
		private:
			uint32_t m_ID;
			mutable std::unordered_map<std::string, int32_t> m_ULocationCache;
		};
	}
}