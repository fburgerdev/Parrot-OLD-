#include "Ptpch.hpp"
#include "PtWindow.hpp"
#include "Assets/AssetManager.hpp"
#include "Utils/FileRead.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"

namespace Parrot
{
	PtWindow::PtWindow(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{
		std::ifstream stream(filepath.GetFullPath());
		InternalLog::LogAssert(stream.is_open(), StreamNotOpenErrorMsg, filepath.GetFullPath());
		
		std::string line;
		std::string key;
		std::string arg;
		while (std::getline(stream, line))
		{
			Utils::GetKey(line, key);
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

	const Utils::Filepath& PtWindow::GetFilepath() const
	{
		return m_Filepath;
	}
	const PtWindow::Data& PtWindow::GetData() const
	{
		return m_Data;
	}
}