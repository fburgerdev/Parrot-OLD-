#pragma once
#include "AssetManager.hpp"

namespace Parrot
{
	namespace AssetManager
	{
		void Internal_InitAssetDir(const Utils::Directory& assetDirectory);
		void Internal_LoadAllFromDir();

		void Internal_ConvertToAsset(const Utils::Filepath& src, const Utils::Directory& dst = Utils::Directory(""));
	}
}