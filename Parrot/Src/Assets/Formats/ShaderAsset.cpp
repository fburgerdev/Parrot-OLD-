#include "Ptpch.hpp"
#include "ShaderAsset.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/Msgs.hpp"

namespace Parrot
{
	namespace Asset
	{
		ShaderAsset::ShaderAsset(const Utils::Filepath& filepath)
			: PtObj(PtObjType::ShaderAsset), m_Filepath(filepath)
		{
			std::ifstream stream(filepath.GetFullPath());
			InternalLog::LogAssert(stream.is_open(), StreamErrorMsg, filepath.GetFullPath());
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
		ShaderAsset::~ShaderAsset()
		{

		}
		const Utils::Filepath& ShaderAsset::GetFilepath() const
		{
			return m_Filepath;
		}
		const ShaderAsset::Data& ShaderAsset::GetData() const
		{
			return m_Data;
		}
	}
}