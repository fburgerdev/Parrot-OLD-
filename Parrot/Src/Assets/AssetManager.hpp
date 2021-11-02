#pragma once 
#include <unordered_map>
#include "Formats/PtTex.hpp"
#include "Formats/PtShader.hpp"
#include "Formats/PtMesh.hpp"
#include "Formats/PtWindow.hpp"
#include "Formats/PtScene.hpp"

namespace Parrot
{
	class AssetManager
	{
	public:
		static void ConvertToAsset(const Utils::Filepath& src, const Utils::Filepath& dst);
		static void ConvertToAssetIfNExist(const Utils::Filepath& src, const Utils::Filepath& dst);

		static void LoadAsset(const Utils::Filepath& filepath);
		static void UnloadAsset(const Utils::Filepath& filepath);

		static const PtTex& GetTexture(const std::string& name);
		static const PtShader& GetShader(const std::string& name);
		static const PtMesh& GetMesh(const std::string& name);
		static const PtWindow& GetWindow(const std::string& name);
		static const PtScene& GetScene(const std::string& name);
	private:
		static std::unordered_map<std::string, PtTex*> s_Textures;
		static std::unordered_map<std::string, PtShader*> s_Shaders;
		static std::unordered_map<std::string, PtMesh*> s_Meshes;
		static std::unordered_map<std::string, PtWindow*> s_Windows;
		static std::unordered_map<std::string, PtScene*> s_Scenes;
	};
}