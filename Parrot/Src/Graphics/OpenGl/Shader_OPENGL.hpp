#pragma once
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	class Shader_OPENGL : public ShaderAPI
	{
	public:
		Shader_OPENGL(const Utils::Filepath& filepath);
		~Shader_OPENGL();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t CompileShader(int32_t shaderType, const std::string& source);
	private:
		uint32_t m_ID;
		Utils::Filepath m_Filepath;
	};
}