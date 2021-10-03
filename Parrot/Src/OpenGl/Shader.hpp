#pragma once
#include "Pch.hpp"
#include "Vector.hpp"
#include <glad/glad.h>

namespace Parrot
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	private:
		uint32_t m_ID;
		std::string m_Filepath;
		std::unordered_map<std::string, int32_t> m_UniformLocationCache;
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		uint32_t GetID() const { return m_ID; }

		// uniforms
		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, Vector::Vec2f vector);
		void SetUniform3f(const std::string& name, Vector::Vec3f vector);
		void SetUniform4f(const std::string& name, Vector::Vec4f vector);

		void SetUniform1i(const std::string& name, int32_t value);

		void SetUniformMat3f(const std::string& name, float* mat, uint32_t transpose = GL_FALSE);
		void SetUniformMat4f(const std::string& name, float* mat, uint32_t transpose = GL_FALSE);
	private:
		uint32_t GetUniformLocation(const std::string& name);
		uint32_t CompileShader(uint32_t type, const std::string& source);
		ShaderProgramSource ParseShader();
		uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	};
}