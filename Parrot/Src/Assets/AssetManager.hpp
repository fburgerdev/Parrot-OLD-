#pragma once 
#include "Formats/TexAsset.hpp"
#include "Formats/ShaderAsset.hpp"
#include "Formats/MeshAsset.hpp"
#include "Formats/WindowAsset.hpp"
#include "Formats/SceneAsset.hpp"

namespace Parrot
{
	// the asset manager handles asset lifetime and gives the opportunity to access assets globaly
	namespace AssetManager
	{
		// lists all supported custom file formats
		enum class AssetFormat : int8_t
		{
			Unknown = -1, Mesh, Shader, Texture, Scene, Window
		};

		// directory handling
		const Utils::Directory& GetAssetDir();

		// asset lifetime
		bool LoadAsset(const Utils::Filename& filename);
		bool IsAssetLoaded(const Utils::Filename& filename);
		void UnloadAsset(const Utils::Filename& filename);

		// asset accessing
		Asset::TexAsset& GetTexAsset(const Utils::Filename& filename);
		Asset::TexAsset& GetTexAsset(const std::string& name);
		Asset::ShaderAsset& GetShaderAsset(const Utils::Filename& filenamee);
		Asset::ShaderAsset& GetShaderAsset(const std::string& name);
		Asset::MeshAsset& GetMeshAsset(const Utils::Filename& filename);
		Asset::MeshAsset& GetMeshAsset(const std::string& name);
		Asset::WindowAsset& GetWindowAsset(const Utils::Filename& filename);
		Asset::WindowAsset& GetWindowAsset(const std::string& name);
		Asset::SceneAsset& GetSceneAsset(const Utils::Filename& filename);
		Asset::SceneAsset& GetSceneAsset(const std::string& name);

		const Asset::MeshAsset& GetQuadMesh();
		const Asset::MeshAsset& GetCubeMesh();
		const Asset::TexAsset& GetWhiteTex();
		const Asset::ShaderAsset& GetStandardShader();
	};
}