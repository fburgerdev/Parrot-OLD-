#include "Pch.hpp"
#include "Shader.hpp"
#include "GlDebug.hpp"
#include "Log.hpp"
#include "Core.hpp"
#include "Application.hpp"
#include <glad/glad.h>

namespace Parrot
{
    Shader::Shader(const std::string& filepath)
    {
        m_Filepath = filepath;
        ShaderProgramSource source = ParseShader();
        m_ID = CreateShader(source.VertexSource, source.FragmentSource);
    }

    Shader::~Shader()
    {
        if (m_ID != 0)
            GlCall(glDeleteProgram(m_ID));
    }

    void Shader::Bind() const
    {
        PT_DEBUG_CALL(if (m_ID == 0) { Log::LogError("Could not bind shader \"%s\"!", m_Filepath.c_str()); Application::ThrowError();})
        GlCall(glUseProgram(m_ID));
    }

    void Shader::Unbind() const
    {
        GlCall(glUseProgram(0));
    }

    // uniforms
    void Shader::SetUniform1f(const std::string& name, float value)
    {
        GlCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform2f(const std::string& name, Vector::Vec2f vector)
    {
        GlCall(glUniform2f(GetUniformLocation(name), vector.x, vector.y));
    }

    void Shader::SetUniform3f(const std::string& name, Vector::Vec3f vector)
    {
        GlCall(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
    }

    void Shader::SetUniform4f(const std::string& name, Vector::Vec4f vector)
    {
        GlCall(glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
    }

    void Shader::SetUniform1i(const std::string& name, int32_t value)
    {
        GlCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniformMat3f(const std::string& name, float* mat, uint32_t transpose)
    {
        GlCall(glUniformMatrix3fv(GetUniformLocation(name), 1, transpose, mat));
    }

    void Shader::SetUniformMat4f(const std::string& name, float* mat, uint32_t transpose)
    {
        GlCall(glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, mat));
    }

    uint32_t Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        GlCall(int32_t location = glGetUniformLocation(m_ID, name.c_str()));
        if (location == -1)
            Log::LogWarning("Uniform \"%s\" doesn't exist in shader \"%s\"", name.c_str(), m_Filepath.c_str());

        m_UniformLocationCache[name] = location;
        return location;
    }

    ShaderProgramSource Shader::ParseShader()
    {
        std::ifstream stream(m_Filepath);
        if (!stream.is_open())
            Log::LogError("Could not find shader \"%s\"!", m_Filepath.c_str());

        enum class ShaderType { VERTEX = 0, FRAGMENT, NONE };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else if (type == ShaderType::NONE)
                continue;
            else if (line.find("#snippet") != std::string::npos)
            {
                //size_t substrStart = line.find('<') + 1;
                //std::string identifier = line.substr(substrStart, line.find('>') - substrStart);
                //ss[(uint32_t)type] << ShaderSnippetLib::GetSnippet(identifier) << '\n';
            }
            else
            {
                ss[(uint32_t)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
    {
        GlCall(uint32_t id = glCreateShader(type));
        const char* src = source.c_str();
        GlCall(glShaderSource(id, 1, &src, nullptr));
        GlCall(glCompileShader(id));

        int32_t result;
        GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            int32_t length;
            GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)_malloca(length * sizeof(char));
            GlCall(glGetShaderInfoLog(id, length, &length, message));
            Log::LogError("Failed to compile shader \"%s\"!\n%s", m_Filepath.c_str(), message);
            GlCall(glDeleteShader(id));
            return 0;
        }
        return id;
    }

    uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GlCall(uint32_t program = glCreateProgram());
        GlCall(uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
        GlCall(uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));
        if (vs == 0 || fs == 0)
            return 0;
        GlCall(glAttachShader(program, vs));
        GlCall(glAttachShader(program, fs));
        GlCall(glLinkProgram(program));
        GlCall(glValidateProgram(program));

        GlCall(glDeleteShader(vs));
        GlCall(glDeleteShader(fs));

        return program;
    }
}