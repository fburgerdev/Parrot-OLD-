#pragma once 
#include "Formats/TexAsset.hpp"
#include "Formats/ShaderAsset.hpp"
#include "Formats/MeshAsset.hpp"
#include "Formats/WindowAsset.hpp"
#include "Formats/SceneAsset.hpp"
#include "Formats/SceneObjAsset.hpp"

namespace Parrot
{
	// the asset manager handles asset lifetime and gives the opportunity to access assets globaly
	namespace AssetManager
	{
		// lists all supported custom file formats
		enum class AssetFormat : int8_t
		{
			Unknown = -1, Mesh, Shader, Texture, Scene, SceneObj, Window
		};

		// directory handling
		const Utils::Directory& GetAssetDir();

		// asset lifetime
		Asset::TexAsset& LoadTexAsset(const Utils::Filename& filename);
		Asset::ShaderAsset& LoadShaderAsset(const Utils::Filename& filenamee);
		Asset::MeshAsset& LoadMeshAsset(const Utils::Filename& filename);
		Asset::WindowAsset& LoadWindowAsset(const Utils::Filename& filename);
		Asset::SceneAsset& LoadSceneAsset(const Utils::Filename& filename);
		Asset::SceneObjAsset& LoadSceneObjAsset(const Utils::Filename& filename);

		Asset::TexAsset& LoadTexAsset(const std::string& name);
		Asset::ShaderAsset& LoadShaderAsset(const std::string& namee);
		Asset::MeshAsset& LoadMeshAsset(const std::string& name);
		Asset::WindowAsset& LoadWindowAsset(const std::string& name);
		Asset::SceneAsset& LoadSceneAsset(const std::string& name);
		Asset::SceneObjAsset& LoadSceneObjAsset(const std::string& name);

		bool IsAssetLoaded(const Utils::Filename& filename);
		void UnloadAsset(const Utils::Filename& filename);

		// asset accessing
		Asset::TexAsset& GetTexAsset(const Utils::Filename& filename);
		Asset::ShaderAsset& GetShaderAsset(const Utils::Filename& filenamee);
		Asset::MeshAsset& GetMeshAsset(const Utils::Filename& filename);
		Asset::WindowAsset& GetWindowAsset(const Utils::Filename& filename);
		Asset::SceneAsset& GetSceneAsset(const Utils::Filename& filename);
		Asset::SceneObjAsset& GetSceneObjAsset(const Utils::Filename& filename);
		
		Asset::TexAsset& GetTexAsset(const std::string& name);
		Asset::ShaderAsset& GetShaderAsset(const std::string& name);
		Asset::MeshAsset& GetMeshAsset(const std::string& name);
		Asset::WindowAsset& GetWindowAsset(const std::string& name);
		Asset::SceneAsset& GetSceneAsset(const std::string& name);
		Asset::SceneObjAsset& GetSceneObjAsset(const std::string& name);

		const Asset::MeshAsset& GetQuadMesh();
		const Asset::MeshAsset& GetCubeMesh();
		const Asset::TexAsset& GetWhiteTex();
		const Asset::ShaderAsset& GetStandardShader();
	};
}