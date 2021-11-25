#include "Ptpch.hpp"
#include "WindowAsset.hpp"
#include "Utils/FileRead.hpp"
#include "Assets/InternalAssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/Msgs.hpp"

namespace Parrot
{
	namespace Asset
	{
		WindowAsset::WindowAsset(const Utils::Filepath& filepath)
			: PtObj(PtObjType::WindowAsset), m_Filepath(filepath)
		{
			std::ifstream stream(filepath.GetFullPath());
			InternalLog::LogAssert(stream.is_open(), StreamErrorMsg, filepath.GetFullPath());

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
						AssetManager::LoadAsset(filename);
					m_Data.scene = filename.GetName();
				}
				else if (key == "Style")
					Utils::GetArg(line, m_Data.style);
				else if (key == "Size")
				{
					Utils::GetArg(line, arg);
					m_Data.size = Utils::ArgToVec2u(arg);
				}
			}
			stream.close();
		}
		const Utils::Filepath& WindowAsset::GetFilepath() const
		{
			return m_Filepath;
		}

		const WindowAsset::Data& WindowAsset::GetData() const
		{
			return m_Data;
		}
	}
}