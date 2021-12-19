#include "Ptpch.hpp"
#include "ShaderAsset.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	namespace Asset
	{
		ShaderAsset::ShaderAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName())
		{
			std::ifstream stream(filepath.FullPath());
			if (PT_FUNC_GUARDS_ENABLED && !stream.is_open())
			{
				DebugOut << FileContextWarning << filepath.FullPath() << Debugstream::EndMsg;
				stream.close();
				return;
			}			
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
			if (PT_FUNC_GUARDS_ENABLED)
			{
				if (vertexSrc.empty())
					DebugOut << AssetSyntaxWarning << "Shader " << filepath << "has no vertex source. Use #vertex to declare the vertex shader section" << Debugstream::EndMsg;
				if (fragmentSrc.empty())
					DebugOut << AssetSyntaxWarning << "Shader " << filepath << "has no fragment source. Use #fragment or #pixel to declare the fragment shader section" << Debugstream::EndMsg;
			}
			stream.close();
		}
		ShaderAsset::ShaderAsset(const std::string& tag)
			: PtObj(tag) {}

		void ShaderAsset::SaveToFile(const Utils::Filepath& filepath)
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