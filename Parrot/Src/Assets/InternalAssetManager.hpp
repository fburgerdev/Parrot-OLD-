#pragma once
#include "AssetManager.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	namespace AssetManager
	{
		void InitAssetDir(const Utils::Directory& assetDirectory);
		void LoadAllFromDir();

		//void ConvertToAsset(const Utils::Filepath& src, const Utils::Filepath& dst);
		//void ConvertToAssetIfNExist(const Utils::Filepath& src, const Utils::Filepath& dst);
	}
}