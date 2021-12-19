#pragma once 
#include "Utils/Filepath.hpp"
#include "Utils/Folder.hpp"

#include "Assets/Formats/MeshAsset.hpp"
#include "Assets/Formats/SceneAsset.hpp"
#include "Assets/Formats/SceneObjAsset.hpp"
#include "Assets/Formats/ShaderAsset.hpp"
#include "Assets/Formats/TexAsset.hpp"
#include "Assets/Formats/WindowAsset.hpp"

namespace Parrot
{
	class AssetManager
	{
	public:
		static const Utils::Directory& GetAssetDir();

		static Asset::MeshAsset& CreateMeshAsset(const std::string& tag);
		static Asset::TexAsset& CreateTexAsset(const std::string& tag);

		static Asset::MeshAsset& GetMeshAsset(const std::string& tag);
		static Asset::SceneAsset& GetSceneAsset(const std::string& tag);
		static Asset::SceneObjAsset& GetSceneObjAsset(const std::string& tag);
		static Asset::ShaderAsset& GetShaderAsset(const std::string& tag);
		static Asset::TexAsset& GetTexAsset(const std::string& tag);
		static Asset::WindowAsset& GetWindowAsset(const std::string& tag);

		static const Asset::MeshAsset& GetQuadMesh();
		static const Asset::MeshAsset& GetCubeMesh();
		static const Asset::TexAsset& GetDefaultTex();
		static const Asset::ShaderAsset& GetDefaultShader();
	};
}