#include "Ptpch.hpp"
#include "ShaderAsset.hpp"

#include "Debug/Internal_Log.hpp"

namespace Parrot
{
	namespace Asset
	{
		ShaderAsset::ShaderAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::ShaderAsset), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath());
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
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
					else if (line.find("fragment") != std::string::npos || line.find("pixel") != std::string::npos)
					{
						index = 1;
						continue;
					}
				}
				if (index != -1)
					ss[index] << line << '\n';
			}
			vertexSrc = ss[0].str();
			fragmentSrc = ss[1].str();
			stream.close();
		}
		ShaderAsset::ShaderAsset()
			: PtObj(PtObj::Type::ShaderAsset)
		{

		}

		void ShaderAsset::SaveToFile()
		{
			constexpr const char* vertexL = "#vertex\n";
			constexpr const char* fragmentL = "#fragment\n";

			std::ofstream stream(filepath.FullPath());
			stream.write(vertexL, std::strlen(vertexL));
			stream.write(vertexSrc.c_str(), vertexSrc.length());
			stream.write(fragmentL, std::strlen(fragmentL));
			stream.write(fragmentSrc.c_str(), fragmentSrc.length());
			stream.put('\0');
			stream.close();
		}
	}
}