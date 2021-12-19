#include "PtPch.hpp"
#include "Constructor.hpp"

namespace Parrot
{
	Asset::MeshAsset& Constructor::MeshAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::MeshAsset(filepath);
	}
	Asset::MeshAsset& Constructor::MeshAssetConstructor(const std::string& tag)
	{
		return *new Asset::MeshAsset(tag);
	}
	Asset::SceneAsset& Constructor::SceneAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::SceneAsset(filepath);
	}
	Asset::SceneObjAsset& Constructor::SceneObjAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::SceneObjAsset(filepath);
	}
	Asset::SceneObjAsset& Constructor::SceneObjAssetConstructor(Utils::FileIn& stream)
	{
		return *new Asset::SceneObjAsset(stream);
	}
	Asset::ShaderAsset& Constructor::ShaderAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::ShaderAsset(filepath);
	}
	Asset::ShaderAsset& Constructor::ShaderAssetConstructor(const std::string& tag)
	{
		return *new Asset::ShaderAsset(tag);
	}
	Asset::TexAsset& Constructor::TexAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::TexAsset(filepath);
	}
	Asset::TexAsset& Constructor::TexAssetConstructor(const std::string& tag)
	{
		return *new Asset::TexAsset(tag);
	}
	Asset::WindowAsset& Constructor::WindowAssetConstructor(const Utils::Filepath& filepath)
	{
		return *new Asset::WindowAsset(filepath);
	}
}