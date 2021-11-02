#include "Ptpch.hpp"
#include "PtShader.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	PtShader::PtShader(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{
		std::ifstream stream(filepath.FullPath());
		InternalLog::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
		std::stringstream ss[2];
		std::string line;
		uint32_t index;
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
		m_Data.vertexSrc = ss[0].str();
		m_Data.fragmentSrc = ss[1].str();
		stream.close();
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