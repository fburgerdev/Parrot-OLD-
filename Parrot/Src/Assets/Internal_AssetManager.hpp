#pragma once
#include "AssetManager.hpp"

namespace Parrot
{
	namespace Internal_AssetManager
	{
		void InitAssetDir(const Utils::Directory& assetDirectory);

		void ConvertToAsset(const Utils::Filepath& src, const Utils::Directory& dst = Utils::Directory());
	}
}