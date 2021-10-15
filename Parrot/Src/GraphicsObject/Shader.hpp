#pragma once
#include "Ptpch.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	namespace GraphicsObject
	{
		class Shader
		{
		private:
			uint32_t m_ID = 0;
		public:
			uint32_t GetID() const { return m_ID; }
		public:
			struct ShaderProgramSource
			{
				std::string VertexSource;
				std::string FragmentSource;
			};
		private:
			std::string m_Filepath;
			std::unordered_map<std::string, int32_t> m_UniformLocationCache;
		public:
			Shader(const std::string& filepath);
			~Shader();

			void Bind() const;
			void Unbind() const;

			// Uniforms
			void SetUniform1f(const std::string& name, float value);
			void SetUniform2f(const std::string& name, Math::Vec2f vector);
			void SetUniform3f(const std::string& name, Math::Vec3f vector);
			void SetUniform4f(const std::string& name, Math::Vec4f vector);

			void SetUniform1i(const std::string& name, int32_t value);

			void SetUniformMat3f(const std::string& name, float* mat, uint32_t transpose = 0);
			void SetUniformMat4f(const std::string& name, float* mat, uint32_t transpose = 0);
		private:
			uint32_t GetUniformLocation(const std::string& name);
			uint32_t CompileShader(uint32_t type, const std::string& source);
			ShaderProgramSource ParseShader();
			uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		};
	}
}