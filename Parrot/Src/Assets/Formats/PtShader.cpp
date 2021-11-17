#include "Ptpch.hpp"
#include "PtShader.hpp"
#include "Utils/FileRead.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"
#include "ClientInterface/Application.hpp"

namespace Parrot
{
	PtShader::PtShader(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{
		std::ifstream stream(filepath.GetFullPath());
		InternalLog::LogAssert(stream.is_open(), StreamNotOpenErrorMsg, filepath.GetFullPath());
		std::stringstream ss[2];
		std::string line;
		int32_t index = -1;
		while (std::getline(stream, line))
		{
			if (line[0] == '#')
			{
				if (line.find("vertex") != std::string::npos)
				{
					index = 0;
					continue;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					index = 1;
					continue;
				}
			}
			if (index != -1)
				ss[index] << line << '\n';
		}
		m_Data.vertexSrc = ss[0].str();
		m_Data.fragmentSrc = ss[1].str();
		stream.close();
	}
	PtShader::~PtShader()
	{
		if (m_ShaderAPI)
			delete m_ShaderAPI;
	}

	const ShaderAPI& PtShader::GetShaderAPI()
	{
		if (!m_ShaderAPI)
		{
			Application::MainWindow().GetWindowAPI().Bind();
			m_ShaderAPI = CreateShaderAPI(m_Data.vertexSrc, m_Data.fragmentSrc);
		}
		return *m_ShaderAPI;
	}
	const Utils::Filepath& PtShader::GetFilepath() const
	{
		return m_Filepath;
	}
	const PtShader::Data& PtShader::GetData() const
	{
		return m_Data;
	}
}