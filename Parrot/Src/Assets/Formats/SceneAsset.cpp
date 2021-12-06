#include "Ptpch.hpp"
#include "SceneAsset.hpp"

#include "Utils/FileRead.hpp"
#include "SceneObjAsset.hpp"
#include "Debug/Internal_Log.hpp"
#include "Assets/Internal_AssetManager.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	namespace Asset
	{
		SceneAsset::SceneAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::Scene), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath());
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
			
			while (!stream.eof())
				sceneObjs.push_back(new SceneObjAsset(stream));
			stream.close();
		}
	}
}