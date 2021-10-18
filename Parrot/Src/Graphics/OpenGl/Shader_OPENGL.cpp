#include "Ptpch.hpp"
#include "Shader_OPENGL.hpp"
#include "Utils/StrFuncs.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Shader_OPENGL::Shader_OPENGL(const Utils::Filepath& filepath)
		: m_ID(0), m_Filepath(filepath)
	{
		InternalLog::LogAssert(Utils::StrIsEqual("GLSL", filepath.Extension().data()), "Couldn't identify shader format in \"%\"! Shaders currently only support \".GLSL\".", filepath.Filename());

		std::ifstream stream(filepath.FullPath().c_str());
		InternalLog::LogAssert(stream.is_open(), "Shader File with path \"%\" couldn't be loaded! Check if the path is correct and the file isn't corrupted.", filepath.FullPath());
		std::stringstream ss[2];
		std::string line;
		int32_t index = -1;
		while (std::getline(stream, line))
		{
			if (line.find("#") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					index = 0;
				else if (line.find("fragment") != std::string::npos)
					index = 1;
			}
			if (index != -1)
				ss[index] << line << '\n';
		}

		m_ID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, ss[0].str());
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, ss[1].str());
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
}