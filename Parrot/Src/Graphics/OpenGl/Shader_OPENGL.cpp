#include "Ptpch.hpp"
#include "Shader_OPENGL.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Shader_OPENGL::Shader_OPENGL(const PtShader& ptShader)
		: m_Filepath(ptShader.GetFilepath()), m_ID(0)
	{
		m_ID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, ptShader.GetData().vertexSrc);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, ptShader.GetData().fragmentSrc);
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

    void Shader_OPENGL::SetUniformInt(const std::string& identifier, int32_t val)
    {
        glUniform1i(GetUniformLocation(identifier), val);
    }
    void Shader_OPENGL::SetUniformVec2i(const std::string& identifier, Math::Vec2i val)
    {
        glUniform2i(GetUniformLocation(identifier), val.x, val.y);
    }
    void Shader_OPENGL::SetUniformVec3i(const std::string& identifier, Math::Vec3i val)
    {
        glUniform3i(GetUniformLocation(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::SetUniformVec4i(const std::string& identifier, Math::Vec4i val)
    {
        glUniform4i(GetUniformLocation(identifier), val.x, val.y, val.z, val.w);
    }

    void Shader_OPENGL::SetUniformFloat(const std::string& identifier, float val)
    {
        glUniform1f(GetUniformLocation(identifier), val);
    }
    void Shader_OPENGL::SetUniformVec2f(const std::string& identifier, Math::Vec2f val)
    {
        glUniform2f(GetUniformLocation(identifier), val.x, val.y);
    }
    void Shader_OPENGL::SetUniformVec3f(const std::string& identifier, Math::Vec3f val)
    {
        glUniform3f(GetUniformLocation(identifier), val.x, val.y, val.z);
    }
    void Shader_OPENGL::SetUniformVec4f(const std::string& identifier, Math::Vec4f val)
    {
        glUniform4f(GetUniformLocation(identifier), val.x, val.y, val.z, val.w);
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

            InternalLog::LogError("Shader \"%\" compilation failed \"%\"!\n%\n%Source Code:", m_Filepath.Filename(), shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment", message, InternalLog::ConsoleColor::White);

        //    std::vector<uint32_t> errorLines;
        //    char* messageCursor = message;
        //    while (*messageCursor != '\0')
        //    {
        //        std::string errorLineString;
        //        while (*messageCursor != '(')
        //        {
        //            if (*messageCursor++ == '\0')
        //                goto LoopExit1;
        //        }
        //        messageCursor++;
        //        while (*messageCursor != ')')
        //        {
        //            if (*messageCursor == '\0')
        //                goto LoopExit1;
        //            errorLineString.push_back(*messageCursor++);
        //        }
        //        errorLines.push_back(std::stoi(errorLineString.c_str()));
        //    }
        //LoopExit1:
        //    const char* sourceCursor = source.c_str();
        //    uint32_t line = 1;
        //    IndentConsoleLine();
        //    std::cout << Log::ConsoleColor::White << "1\t";
        //    while (*sourceCursor != '\0')
        //    {
        //    LoopExit2:
        //        std::cout << *sourceCursor;
        //        if (*sourceCursor++ == '\n' && *sourceCursor != '\0')
        //        {
        //            IndentConsoleLine();
        //            for (uint32_t i = 0; i < errorLines.size(); i++)
        //            {
        //                if (line == errorLines[i])
        //                {
        //                    std::cout << Log::ConsoleColor::Red << ++line << '\t';
        //                    goto LoopExit2;
        //                }
        //            }
        //            std::cout << Log::ConsoleColor::White << line++ << '\t';
        //        }
        //    }

            glDeleteShader(id);
            delete[] message;
            return 0;
        }

        InternalLog::LogInfo("% Shader \"%\" compilation successful!", shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment", m_Filepath.Filename());
        return id;
	}
    uint32_t Shader_OPENGL::GetUniformLocation(const std::string& identifier)
    {
        if (m_ULocationCache.find(identifier) != m_ULocationCache.end())
            return m_ULocationCache[identifier];
        int32_t location = glGetUniformLocation(m_ID, identifier.c_str());
        if (location == -1)
            InternalLog::LogWarning("Uniform \"%s\" doesn't exist in shader \"%s\"", identifier.c_str(), m_Filepath.FilenameNExt());

        m_ULocationCache[identifier] = location;
        return location;
    }
}