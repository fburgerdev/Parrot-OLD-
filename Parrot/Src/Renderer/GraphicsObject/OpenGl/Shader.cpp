#include "Ptpch.hpp"
#ifdef PT_OPENGL
    #include "Renderer/GraphicsObject/Shader.hpp"
    #include "GlDebug.hpp"
    #include "Utils/StrFuncs.hpp"

    namespace Parrot
    {
        // defined in "Log.cpp"
        void IndentConsoleLine();
        namespace GraphicsObject
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
                Log::LogAssert(m_ID != 0, "Could not bind shader \"%\"!", Utils::FilenameFromPath(m_Filepath.c_str()));
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

            void Shader::SetUniform2f(const std::string& name, Math::Vec2f vector)
            {
                GlCall(glUniform2f(GetUniformLocation(name), vector.x, vector.y));
            }

            void Shader::SetUniform3f(const std::string& name, Math::Vec3f vector)
            {
                GlCall(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
            }

            void Shader::SetUniform4f(const std::string& name, Math::Vec4f vector)
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
                    Log::LogWarning("Uniform \"%\" doesn't exist in shader \"%\"", name.c_str(), m_Filepath.c_str());

                m_UniformLocationCache[name] = location;
                return location;
            }

            Shader::ShaderProgramSource Shader::ParseShader()
            {
                std::ifstream stream(m_Filepath);
                if (!stream.is_open())
                {
                    Log::LogError("Could not find shader \"%\"!", m_Filepath.c_str());
                    return { "", "" };
                }
                enum class ShaderType { VERTEX = 0, FRAGMENT, NONE };

                std::string line;
                std::stringstream ss[2];
                ShaderType type = ShaderType::NONE;
                while (std::getline(stream, line))
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
                if (source.size() == 0)
                    return 0;
                GlCall(uint32_t id = glCreateShader(type));
                const char* src = source.c_str();
                GlCall(glShaderSource(id, 1, &src, nullptr));
                GlCall(glCompileShader(id));

                const char* shaderType = type == GL_VERTEX_SHADER ? "Vertex" : "Fragment";

                int32_t result;
                GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
                if (result == GL_FALSE)
                {
                    int32_t length;
                    GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
                    char* message = new char[length];
                    GlCall(glGetShaderInfoLog(id, length, &length, message));
                
                    Log::LogError("Shader % compilation failed \"%\"!\n%\n%Source Code:", shaderType, Utils::FilenameFromPath(m_Filepath.c_str()), message, Log::ConsoleColor::White);
          
                    std::vector<uint32_t> errorLines;
                    char* messageCursor = message;
                    while (*messageCursor != '\0')
                    {
                        std::string errorLineString;
                        while (*messageCursor != '(')
                        {
                            if (*messageCursor++ == '\0')
                                goto LoopExit1;
                        }
                        messageCursor++;
                        while (*messageCursor != ')')
                        {
                            if (*messageCursor == '\0')
                                goto LoopExit1;
                            errorLineString.push_back(*messageCursor++);
                        }
                        errorLines.push_back(std::stoi(errorLineString.c_str()));
                    }
                    LoopExit1:
                    const char* sourceCursor = source.c_str();
                    uint32_t line = 1;
                    IndentConsoleLine();
                    std::cout << Log::ConsoleColor::White << "1\t";
                    while (*sourceCursor != '\0')
                    {
                        LoopExit2:
                        std::cout << *sourceCursor;
                        if (*sourceCursor++ == '\n' && *sourceCursor != '\0')
                        {
                            IndentConsoleLine();
                            for (uint32_t i = 0; i < errorLines.size(); i++)
                            {
                                if (line == errorLines[i])
                                {
                                    std::cout << Log::ConsoleColor::Red << ++line << '\t';
                                    goto LoopExit2;
                                }
                            }
                            std::cout << Log::ConsoleColor::White << line++ << '\t';
                        }
                    }

                    GlCall(glDeleteShader(id));
                    delete[] message;
                    return 0;
                }
                Log::LogInfo("% Shader \"%\" compilation successful!", shaderType, Utils::FilenameFromPath(m_Filepath.c_str()));
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
    }
#endif