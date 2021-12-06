#include "Ptpch.hpp"
#include "AssetManager.hpp"
#include "Internal_AssetManager.hpp"

#include "Assets/StandardAssets.hpp"
#include "Debug/Internal_Log.hpp"

#include "Vendor/STB/stb_image.h"

#define PT_MESH_EXT "MSH"
#define PT_SHADER_EXT "SHDR"
#define PT_TEXTURE_EXT "TXTR"
#define PT_SCENE_EXT "SCN"
#define PT_SCENEOBJ_EXT "SCNOBJ"
#define PT_WINDOW_EXT "WNDW"
#define PT_VALID_FORMAT_LIST "MSH, SHDR, TXTR, SCN, SCNOBJ, WNDW"

namespace Parrot
{
	static Utils::Directory s_AssetDirectory;
	static std::unordered_map<std::string, std::string> s_FilenameToPath;
	
	static std::unordered_map<std::string, Asset::TexAsset*> s_TexAssets;
	static std::unordered_map<std::string, Asset::ShaderAsset*> s_ShaderAssets;
	static std::unordered_map<std::string, Asset::MeshAsset*> s_MeshAssets;
	static std::unordered_map<std::string, Asset::WindowAsset*> s_WindowAssets;
	static std::unordered_map<std::string, Asset::SceneAsset*> s_SceneAssets;
	static std::unordered_map<std::string, Asset::SceneObjAsset*> s_SceneObjAssets;

	static AssetManager::AssetFormat GetAssetFormatFromExt(std::string_view ext)
	{
		if (ext == PT_MESH_EXT)
			return AssetManager::AssetFormat::Mesh;
		else if (ext == PT_SHADER_EXT)
			return AssetManager::AssetFormat::Shader;
		else if (ext == PT_TEXTURE_EXT)
			return AssetManager::AssetFormat::Texture;
		else if (ext == PT_SCENE_EXT)
			return AssetManager::AssetFormat::Scene;
		else if (ext == PT_SCENEOBJ_EXT)
			return AssetManager::AssetFormat::SceneObj;
		else if (ext == PT_WINDOW_EXT)
			return AssetManager::AssetFormat::Window;
		return AssetManager::AssetFormat::Unknown;
	}

	const Utils::Directory& AssetManager::GetAssetDir()
	{
		return s_AssetDirectory;
	}

	bool AssetManager::IsAssetLoaded(const Utils::Filename& filename)
	{
		AssetFormat format = GetAssetFormatFromExt(filename.GetExt());
		switch (format)
		{
		case AssetFormat::Texture:
			return s_TexAssets.find(filename.String()) != s_TexAssets.end();
		case AssetFormat::Shader:
			return s_ShaderAssets.find(filename.String()) != s_ShaderAssets.end();
		case AssetFormat::Mesh:
			return s_MeshAssets.find(filename.String()) != s_MeshAssets.end();
		case AssetFormat::Window:
			return s_WindowAssets.find(filename.String()) != s_WindowAssets.end();
		case AssetFormat::Scene:
			return s_SceneAssets.find(filename.String()) != s_SceneAssets.end();
		case AssetFormat::SceneObj:
			return s_SceneObjAssets.find(filename.String()) != s_SceneObjAssets.end();
		default:
			return false;
		}
		return false;
	}
	void AssetManager::UnloadAsset(const Utils::Filename& filename)
	{
		AssetFormat format = GetAssetFormatFromExt(filename.GetExt());
		switch (format)
		{
		case AssetFormat::Texture:
			PT_GUARD_CALL(if (s_TexAssets.find(filename.String()) == s_TexAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_TexAssets[filename.String()];
			s_TexAssets.erase(filename.String());
			return;
		case AssetFormat::Shader:
			PT_GUARD_CALL(if (s_ShaderAssets.find(filename.String()) == s_ShaderAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_ShaderAssets[filename.String()];
			s_ShaderAssets.erase(filename.String());
			return;
		case AssetFormat::Mesh:
			PT_GUARD_CALL(if (s_MeshAssets.find(filename.String()) == s_MeshAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_MeshAssets[filename.String()];
			s_MeshAssets.erase(filename.String());
			return;
		case AssetFormat::Window:
			PT_GUARD_CALL(if (s_WindowAssets.find(filename.String()) == s_WindowAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_WindowAssets[filename.String()];
			s_WindowAssets.erase(filename.String());
			return;
		case AssetFormat::Scene:
			PT_GUARD_CALL(if (s_SceneAssets.find(filename.String()) == s_SceneAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_SceneAssets[filename.String()];
			s_SceneAssets.erase(filename.String());
			return;
		case AssetFormat::SceneObj:
			PT_GUARD_CALL(if (s_SceneObjAssets.find(filename.String()) == s_SceneObjAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_SceneObjAssets[filename.String()];
			s_SceneObjAssets.erase(filename.String());
			return;
		default:
			return;
		}
	}

	Asset::TexAsset& AssetManager::LoadTexAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_TexAssets.find(filename.String()) != s_TexAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_TexAssets[filename.String()];
			}
		)
		Asset::TexAsset* asset = new Asset::TexAsset(s_FilenameToPath[filename.String()]);
		s_TexAssets[filename.String()] = asset;
		return *asset;
	}
	Asset::ShaderAsset& AssetManager::LoadShaderAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_ShaderAssets.find(filename.String()) != s_ShaderAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_ShaderAssets[filename.String()];
			}
		)
		Asset::ShaderAsset* asset = new Asset::ShaderAsset(s_FilenameToPath[filename.String()]);
		s_ShaderAssets[filename.String()] = asset;
		return *asset;
	}
	Asset::MeshAsset& AssetManager::LoadMeshAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_MeshAssets.find(filename.String()) != s_MeshAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_MeshAssets[filename.String()];
			}
		)
		Asset::MeshAsset* asset = new Asset::MeshAsset(s_FilenameToPath[filename.String()]);
		s_MeshAssets[filename.String()] = asset;
		return *asset;
	}
	Asset::WindowAsset& AssetManager::LoadWindowAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_WindowAssets.find(filename.String()) != s_WindowAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_WindowAssets[filename.String()];
			}
		)
		Asset::WindowAsset* asset = new Asset::WindowAsset(s_FilenameToPath[filename.String()]);
		s_WindowAssets[filename.String()] = asset;
		return *asset;
	}
	Asset::SceneAsset& AssetManager::LoadSceneAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_SceneAssets.find(filename.String()) != s_SceneAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_SceneAssets[filename.String()];
			}
		)
		Asset::SceneAsset* asset = new Asset::SceneAsset(s_FilenameToPath[filename.String()]);
		s_SceneAssets[filename.String()] = asset;
		return *asset;
	}
	Asset::SceneObjAsset& AssetManager::LoadSceneObjAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_FilenameToPath.find(filename.String()) != s_FilenameToPath.end(), "Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
		PT_GUARD_CALL
		(
			if (s_SceneObjAssets.find(filename.String()) != s_SceneObjAssets.end())
			{
				Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return *s_SceneObjAssets[filename.String()];
			}
		)
		Asset::SceneObjAsset* asset = new Asset::SceneObjAsset(s_FilenameToPath[filename.String()]);
		s_SceneObjAssets[filename.String()] = asset;
		return *asset;
	}

	Asset::TexAsset& AssetManager::LoadTexAsset(const std::string& name)
	{
		return LoadTexAsset(Utils::Filename(name + '.' + PT_TEXTURE_EXT));
	}
	Asset::ShaderAsset& AssetManager::LoadShaderAsset(const std::string& name)
	{
		return LoadShaderAsset(Utils::Filename(name + '.' + PT_SHADER_EXT));
	}
	Asset::MeshAsset& AssetManager::LoadMeshAsset(const std::string& name)
	{
		return LoadMeshAsset(Utils::Filename(name + '.' + PT_MESH_EXT));
	}
	Asset::WindowAsset& AssetManager::LoadWindowAsset(const std::string& name)
	{
		return LoadWindowAsset(Utils::Filename(name + '.' + PT_WINDOW_EXT));
	}
	Asset::SceneAsset& AssetManager::LoadSceneAsset(const std::string& name)
	{
		return LoadSceneAsset(Utils::Filename(name + '.' + PT_SCENE_EXT));
	}
	Asset::SceneObjAsset& AssetManager::LoadSceneObjAsset(const std::string& name)
	{
		return LoadSceneObjAsset(Utils::Filename(name + '.' + PT_SCENEOBJ_EXT));
	}

	static constexpr const char* AssetAccessErrorMsg = "Couldn't find loaded asset \"%\" in asset manager. Either the asset wasn't loaded in the first place or the name was misspelled.";
	Asset::TexAsset& AssetManager::GetTexAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_TexAssets.find(filename.String()) != s_TexAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::TexAsset*)s_TexAssets[filename.String()];
	}
	Asset::ShaderAsset& AssetManager::GetShaderAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_ShaderAssets.find(filename.String()) != s_ShaderAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::ShaderAsset*)s_ShaderAssets[filename.String()];
	}
	Asset::MeshAsset& AssetManager::GetMeshAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_MeshAssets.find(filename.String()) != s_MeshAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::MeshAsset*)s_MeshAssets[filename.String()];
	}
	Asset::WindowAsset& AssetManager::GetWindowAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_WindowAssets.find(filename.String()) != s_WindowAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::WindowAsset*)s_WindowAssets[filename.String()];
	}
	Asset::SceneAsset& AssetManager::GetSceneAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_SceneAssets.find(filename.String()) != s_SceneAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::SceneAsset*)s_SceneAssets[filename.String()];
	}
	Asset::SceneObjAsset& AssetManager::GetSceneObjAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_SceneObjAssets.find(filename.String()) != s_SceneObjAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::SceneObjAsset*)s_SceneObjAssets[filename.String()];
	}

	Asset::TexAsset& AssetManager::GetTexAsset(const std::string& name)
	{
		return GetTexAsset(Utils::Filename(name + '.' + PT_TEXTURE_EXT));
	}
	Asset::ShaderAsset& AssetManager::GetShaderAsset(const std::string& name)
	{
		return GetShaderAsset(Utils::Filename(name + '.' + PT_SHADER_EXT));
	}
	Asset::MeshAsset& AssetManager::GetMeshAsset(const std::string& name)
	{
		return GetMeshAsset(Utils::Filename(name + '.' + PT_MESH_EXT));
	}
	Asset::WindowAsset& AssetManager::GetWindowAsset(const std::string& name)
	{
		return GetWindowAsset(Utils::Filename(name + '.' + PT_WINDOW_EXT));
	}
	Asset::SceneAsset& AssetManager::GetSceneAsset(const std::string& name)
	{
		return GetSceneAsset(Utils::Filename(name + '.' + PT_SCENE_EXT));
	}
	Asset::SceneObjAsset& AssetManager::GetSceneObjAsset(const std::string& name)
	{
		return GetSceneObjAsset(Utils::Filename(name + '.' +  PT_SCENEOBJ_EXT));
	}

	const Asset::MeshAsset& AssetManager::GetQuadMesh()
	{
		return Asset::quadMesh;
	}
	const Asset::MeshAsset& AssetManager::GetCubeMesh()
	{
		return Asset::cubeMesh;
	}
	const Asset::TexAsset& AssetManager::GetWhiteTex()
	{
		return Asset::whiteTex;
	}
	const Asset::ShaderAsset& AssetManager::GetStandardShader()
	{
		return Asset::standardShader;
	}

	// maps all filenames in the asset directory to their actual location so we don't have to mess with filepaths later on
	void Internal_AssetManager::InitAssetDir(const Utils::Directory& assetDirectory)
	{
		s_AssetDirectory = assetDirectory;
		for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(assetDirectory.String()))
		{
			Utils::Filepath filepath(dirEntry.path().string());
			if (GetAssetFormatFromExt(filepath.GetFilename().GetExt()) != AssetManager::AssetFormat::Unknown)
				s_FilenameToPath[filepath.GetFilename().String()] = std::move(filepath.FullPath());
		}
	}

	void Internal_AssetManager::LoadImageFromFilename(const Utils::Filename& filename, Math::Vec2u& size, Math::Vec4u8* buffer)
	{
		std::string_view ext = filename.GetExt();
		if (ext == "png" || ext == "jpg")
		{
			int32_t colorChannels = 4;
			stbi_set_flip_vertically_on_load(true);
			int32_t width, height, BPP;
			buffer = (Math::Vec4u8*)stbi_load((s_AssetDirectory.String() + filename.String()).c_str(), &width, &height, &BPP, colorChannels);
			size.x = width;
			size.y = height;
			PT_GUARD_CALL
			(
				if (!buffer)
					Internal_Log::LogWarning("Texture \"%\" couldn't be loaded. Check if the filename is correct and the file isn't corrupted.", filename.String());
			)
		}
		else
		{
			Internal_Log::LogWarning("Src extension in \"%\" isn't supported! Supported formats are \"jpg\" and \"png\"", filename.String());
		}
	}
}