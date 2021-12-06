#pragma once
#include "AssetManager.hpp"

namespace Parrot
{
	namespace Internal_AssetManager
	{
		void InitAssetDir(const Utils::Directory& assetDirectory);

		void LoadImageFromFilename(const Utils::Filename& filename, Math::Vec2u& size, Math::Vec4u8* buffer);
	}
}