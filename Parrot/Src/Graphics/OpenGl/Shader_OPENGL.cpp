#include "Ptpch.hpp"
#include "Shader_OPENGL.hpp"
#include "Debug/InternalLog.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	Shader_OPENGL::Shader_OPENGL(const std::string& vertexSrc, const std::string& fragmentSrc)
	    : m_ID(0)
	{
		m_ID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
		glAttachShader(m_ID, vs);
		glAttachShader(m_ID, fs);
		glLinkProgram(m_ID);
		glValidateProgram(m_ID);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	Shader_OPENGL::~Shader_OPENGL()
	{
		glDeleteProgram(m_ID);
	}

	void Shader_OPENGL::Bind() const
	{
		glUseProgram(m_ID);
	}
	void Shader_OPENGL::Unbind() const
	{
		glUseProgram(0);
	}

    void Shader_OPENGL::SetUniformInt(const std::string& identifier, int32_t val) const
    {
        glUniform1i(GetUniformLocation(identifier), val);
    }
    void Shader_OPENGL::SetUniformVec2i(const std::string& identifier, const Math::Vec2i& val) const
    {
        glUniform2i(GetUniformLocation(identifier), val.x, val.y);
    }
    void Shader_OPENGL::SetUniformVec3i(const std::string& identifier, const Math::Vec3i& val) const
    {
        glUniform3i(GetUniformLocation(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::SetUniformVec4i(const std::string& identifier, const Math::Vec4i& val) const
    {
        glUniform4i(GetUniformLocation(identifier), val.x, val.y, val.z, val.w);
    }

    void Shader_OPENGL::SetUniformFloat(const std::string& identifier, float val) const
    {
        glUniform1f(GetUniformLocation(identifier), val);
    }
    void Shader_OPENGL::SetUniformVec2f(const std::string& identifier, const Math::Vec2f& val) const
    {
        glUniform2f(GetUniformLocation(identifier), val.x, val.y);
    }
    void Shader_OPENGL::SetUniformVec3f(const std::string& identifier, const Math::Vec3f& val) const
    {
        glUniform3f(GetUniformLocation(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::SetUniformVec4f(const std::string& identifier, const Math::Vec4f& val) const
    {
        glUniform4f(GetUniformLocation(identifier), val.x, val.y, val.z, val.w);
    }
    void Shader_OPENGL::SetUniformMat2f(const std::string& identifier, const Math::Mat2f& mat) const
    {
        glUniformMatrix2fv(GetUniformLocation(identifier), 1, GL_FALSE, mat.Raw());
    }
    void Shader_OPENGL::SetUniformMat3f(const std::string& identifier, const Math::Mat3f& mat) const
    {
        glUniformMatrix3fv(GetUniformLocation(identifier), 1, GL_FALSE, mat.Raw());
    }
    void Shader_OPENGL::SetUniformMat4f(const std::string& identifier, const Math::Mat4f& mat) const
    {
        glUniformMatrix4fv(GetUniformLocation(identifier), 1, GL_FALSE, mat.Raw());
    }

	uint32_t Shader_OPENGL::CompileShader(int32_t shaderType, const std::string& source)
	{
        uint32_t id = glCreateShader(shaderType);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        int32_t result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        
        if (result == GL_FALSE)
        {
            int32_t length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(id, length, &length, message);
            glDeleteShader(id);
            InternalLog::LogWarning("%", message);
            delete[] message;
            return 0;
        }
        return id;
	}
    uint32_t Shader_OPENGL::GetUniformLocation(const std::string& identifier) const
    {
        if (m_ULocationCache.find(identifier) != m_ULocationCache.end())
            return m_ULocationCache[identifier];
        int32_t location = glGetUniformLocation(m_ID, identifier.c_str());

        m_ULocationCache[identifier] = location;
        return location;
    }
}