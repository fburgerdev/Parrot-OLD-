#pragma once 
#include "Formats/PtTex.hpp"
#include "Formats/PtShader.hpp"
#include "Formats/PtMesh.hpp"
#include "Formats/PtWindow.hpp"
#include "Formats/PtScene.hpp"

namespace Parrot
{
	// the asset manager handles asset lifetime and gives the opportunity to access assets globaly
	namespace AssetManager
	{
		// lists all supported custom file formats
		enum class Format : int8_t
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
		PtTex& GetTextureAsset(const Utils::Filename& filename);
		PtTex& GetTextureAsset(const std::string& name);
		PtShader& GetShaderAsset(const Utils::Filename& filenamee);
		PtShader& GetShaderAsset(const std::string& name);
		PtMesh& GetMeshAsset(const Utils::Filename& filename);
		PtMesh& GetMeshAsset(const std::string& name);
		PtWindow& GetWindowAsset(const Utils::Filename& filename);
		PtWindow& GetWindowAsset(const std::string& name);
		PtScene& GetSceneAsset(const Utils::Filename& filename);
		PtScene& GetSceneAsset(const std::string& name);
	}
}