#include "Ptpch.hpp"
#include "WindowAsset.hpp"

#include "Utils/FileRead.hpp"
#include "Assets/Internal_AssetManager.hpp"
#include "Debug/Internal_Log.hpp"

namespace Parrot
{
	namespace Asset
	{
		WindowAsset::WindowAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::WindowAsset), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath());
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());

			std::string line;
			std::string key;
			std::string arg;
			while (std::getline(stream, line))
			{
				Utils::GetKey(line, key);
				if (line.find("//") != line.npos)
					line = line.substr(0, line.find("//"));
				if (key == "Scene")
				{
					Utils::GetArg(line, arg);
					Utils::Filename filename(arg);
					if (!AssetManager::IsAssetLoaded(filename))
						scene = &AssetManager::LoadSceneAsset(filename);
					else
						scene = &AssetManager::GetSceneAsset(filename);
				}
				else if (key == "Style")
					Utils::GetArg(line, style);
				else if (key == "Size")
				{
					Utils::GetArg(line, arg);
					size = Utils::ArgToVec2u(arg);
				}
			}
			stream.close();
		}
	}
}