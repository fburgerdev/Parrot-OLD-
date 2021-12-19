#pragma once
#include "Assets/AssetManager.hpp"

namespace Parrot
{
	/*namespace Asset
	{
		class MeshAsset;
		class SceneAsset;
		class SceneObjAsset;
		class ShaderAsset;
		class TexAsset;
		class WindowAsset;
	}*/
	class Constructor
	{
	public:
		static Asset::MeshAsset& MeshAssetConstructor(const Utils::Filepath& filepath);
		static Asset::MeshAsset& MeshAssetConstructor(const std::string& tag);
		static Asset::SceneAsset& SceneAssetConstructor(const Utils::Filepath& filepath);
		static Asset::SceneObjAsset& SceneObjAssetConstructor(const Utils::Filepath& filepath);
		static Asset::SceneObjAsset& SceneObjAssetConstructor(Utils::FileIn& stream);
		static Asset::ShaderAsset& ShaderAssetConstructor(const Utils::Filepath& filepath);
		static Asset::ShaderAsset& ShaderAssetConstructor(const std::string& tag);
		static Asset::TexAsset& TexAssetConstructor(const Utils::Filepath& filepath);
		static Asset::TexAsset& TexAssetConstructor(const std::string& tag);
		static Asset::WindowAsset& WindowAssetConstructor(const Utils::Filepath& filepath);
	};
}