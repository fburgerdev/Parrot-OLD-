#pragma once
#include "Graphics/GraphicsAPI.hpp"
#include <unordered_map>

namespace Parrot
{
	class Shader_OPENGL : public ShaderAPI
	{
	public:
		Shader_OPENGL(const PtShader& ptShader);
		~Shader_OPENGL();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniformInt(const std::string& identifier, int32_t val) override;
		virtual void SetUniformVec2i(const std::string& identifier, Math::Vec2i val) override;
		virtual void SetUniformVec3i(const std::string& identifier, Math::Vec3i val) override;
		virtual void SetUniformVec4i(const std::string& identifier, Math::Vec4i val) override;

		virtual void SetUniformFloat(const std::string& identifier, float val) override;
		virtual void SetUniformVec2f(const std::string& identifier, Math::Vec2f val) override;
		virtual void SetUniformVec3f(const std::string& identifier, Math::Vec3f val) override;
		virtual void SetUniformVec4f(const std::string& identifier, Math::Vec4f val) override;
	private:
		uint32_t CompileShader(int32_t shaderType, const std::string& source);
		uint32_t GetUniformLocation(const std::string& identifier);
	private:
		Utils::Filepath m_Filepath;
		uint32_t m_ID;
		std::unordered_map<std::string, int32_t> m_ULocationCache;
	};
}