#include "Ptpch.hpp"
#include "WindowAsset.hpp"
#include "Debug/Debugstream.hpp"

#include "Assets/AssetRead.hpp"
#include "Assets/AssetManager.hpp"

namespace Parrot
{
	namespace Asset
	{
		WindowAsset::WindowAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName()), scene(nullptr)
		{
			std::ifstream stream(filepath.FullPath());
			if (PT_FUNC_GUARDS_ENABLED && !stream.is_open())
			{
				DebugOut << FileContextWarning << filepath.FullPath() << Debugstream::EndMsg;
				stream.close();
				return;
			}
			std::string assertMsg = filepath.FullPath();
			
			std::string line;
			std::string key;
			std::string arg;
			while (std::getline(stream, line))
			{
				AssetSyntaxAssert(GetKey(line, key), assertMsg);
				if (line.find("//") != line.npos)
					line = line.substr(0, line.find("//"));
				if (key == "scene")
				{
					AssetSyntaxAssert(GetArg(line, arg), assertMsg);
					scene = &AssetManager::GetSceneAsset(arg);
				}
				else if (key == "style")
						AssetSyntaxAssert(GetArg(line, style), assertMsg);
				else if (key == "size")
				{
					AssetSyntaxAssert(GetArg(line, arg), assertMsg);
					AssetSyntaxAssert(ArgToVec2u(arg, size), assertMsg);
				}
			}
			stream.close();
		}
	}
}