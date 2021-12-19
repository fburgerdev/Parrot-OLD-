#include "Ptpch.hpp"
#include "SceneAsset.hpp"
#include "Debug/Debugstream.hpp"
#include "Utils/Filestream.hpp"
#include "Core/Constructor.hpp"

namespace Parrot
{
	namespace Asset
	{
		SceneObjAsset& SceneObjAssetConstructor(Utils::FileIn& stream);
		SceneAsset::SceneAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName())
		{
			Utils::FileIn stream(filepath);
			if (!stream.is_open())
				return;

			while (!stream.eof())
				sceneObjAssets.push_back(&Constructor::SceneObjAssetConstructor(stream));
			stream.close();
		}
	}
}