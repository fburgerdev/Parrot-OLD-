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
#define PT_WINDOW_EXT "WNDW"
#define PT_VALID_FORMAT_LIST "MSH, SHDR, TXTR, SCN, WNDW"

namespace Parrot
{
	static Utils::Directory s_AssetDirectory;
	static std::unordered_map<std::string, std::string> s_FilenameToPath;
	static std::unordered_map<std::string, void*> s_LoadedAssets;

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
		else if (ext == PT_WINDOW_EXT)
			return AssetManager::AssetFormat::Window;
		return AssetManager::AssetFormat::Unknown;
	}

	const Utils::Directory& AssetManager::GetAssetDir()
	{
		return s_AssetDirectory;
	}

	bool AssetManager::LoadAsset(const Utils::Filename& filename)
	{
		AssetManager::AssetFormat format = GetAssetFormatFromExt(filename.GetExt());
		PT_GUARD_CALL(
		if (format == AssetFormat::Unknown)
		{
			Internal_Log::LogWarning("Trying to load asset of unknown format \"%\"! Try using one of these formats \"%\"", filename.String(), PT_VALID_FORMAT_LIST);
			return false;
		}
		if (s_FilenameToPath.find(filename.String()) == s_FilenameToPath.end())
		{
			Internal_Log::LogWarning("Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
			return false;
		}
		if (s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end())
		{
			Internal_Log::LogWarning("Asset \"%\" was already loaded!", filename.String());
			return false;
		})

		switch (format)
		{
		case AssetFormat::Mesh:
			s_LoadedAssets[filename.String()] = new Asset::MeshAsset(s_FilenameToPath[filename.String()]);
			return true;
		case AssetFormat::Shader:
			s_LoadedAssets[filename.String()] = new Asset::ShaderAsset(s_FilenameToPath[filename.String()]);
			return true;
		case AssetFormat::Texture:
			s_LoadedAssets[filename.String()] = new Asset::TexAsset(s_FilenameToPath[filename.String()]);
			return true;
		case AssetFormat::Scene:
			s_LoadedAssets[filename.String()] = new Asset::SceneAsset(s_FilenameToPath[filename.String()]);
			return true;
		case AssetFormat::Window:
			s_LoadedAssets[filename.String()] = new Asset::WindowAsset(s_FilenameToPath[filename.String()]);
			return true;
		default:
			return false;
		}
		return false;
	}
	bool AssetManager::IsAssetLoaded(const Utils::Filename& filename)
	{
		return s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end();
	}
	void AssetManager::UnloadAsset(const Utils::Filename& filename)
	{
		PT_GUARD_CALL(if (s_LoadedAssets.find(filename.String()) == s_LoadedAssets.end())
		{
			Internal_Log::LogWarning("Asset \"%\" is not loaded!", filename.String());
			return;
		})
		delete s_LoadedAssets[filename.String()];
		s_LoadedAssets.erase(filename.String());
	}

	static constexpr const char* AssetAccessErrorMsg = "Couldn't find loaded asset \"%\" in asset manager. Either the asset wasn't loaded in the first place or the name was misspelled.";
	Asset::TexAsset& AssetManager::GetTexAsset(const std::string& name)
	{
		std::string filename = name + '.' + PT_TEXTURE_EXT;
		Internal_Log::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename);
		return *(Asset::TexAsset*)s_LoadedAssets[filename];
	}
	Asset::ShaderAsset& AssetManager::GetShaderAsset(const std::string& name)
	{
		std::string filename = name + '.' + PT_SHADER_EXT;
		Internal_Log::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename);
		return *(Asset::ShaderAsset*)s_LoadedAssets[filename];
	}
	Asset::MeshAsset& AssetManager::GetMeshAsset(const std::string& name)
	{
		std::string filename = name + '.' + PT_MESH_EXT;
		Internal_Log::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename);
		return *(Asset::MeshAsset*)s_LoadedAssets[filename];
	}
	Asset::WindowAsset& AssetManager::GetWindowAsset(const std::string& name)
	{
		std::string filename = name + '.' + PT_WINDOW_EXT;
		Internal_Log::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename);
		return *(Asset::WindowAsset*)s_LoadedAssets[filename];
	}
	Asset::SceneAsset& AssetManager::GetSceneAsset(const std::string& name)
	{
		std::string filename = name + '.' + PT_SCENE_EXT;
		Internal_Log::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename);
		return *(Asset::SceneAsset*)s_LoadedAssets[filename];
	}
	Asset::TexAsset& AssetManager::GetTexAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::TexAsset*)s_LoadedAssets[filename.String()];
	}
	Asset::ShaderAsset& AssetManager::GetShaderAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::ShaderAsset*)s_LoadedAssets[filename.String()];
	}
	Asset::MeshAsset& AssetManager::GetMeshAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::MeshAsset*)s_LoadedAssets[filename.String()];
	}
	Asset::WindowAsset& AssetManager::GetWindowAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::WindowAsset*)s_LoadedAssets[filename.String()];
	}
	Asset::SceneAsset& AssetManager::GetSceneAsset(const Utils::Filename& filename)
	{
		Internal_Log::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessErrorMsg, filename.String());
		return *(Asset::SceneAsset*)s_LoadedAssets[filename.String()];
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
	/*void Internal_AssetManager::LoadAllFromDir()
	{
		for (auto& pair : s_FilenameToPath)
		{
			Utils::Filename filename(pair.first);
			AssetManager::AssetFormat format = GetAssetFormatFromExt(filename.GetExt());
			if (!AssetManager::IsAssetLoaded(filename))
				AssetManager::LoadAsset(filename);
		}
	}*/

	void Internal_AssetManager::ConvertToAsset(const Utils::Filepath& src, const Utils::Directory& dst)
	{
		std::string_view srcExt = src.GetFilename().GetExt();
		if (srcExt == "png" || srcExt == "jpg")
		{
			int32_t colorChannels = 4;
			stbi_set_flip_vertically_on_load(true);
			int32_t width, height, BPP;
			uint8_t* buffer = stbi_load(src.FullPath().c_str(), &width, &height, &BPP, colorChannels);
			PT_GUARD_CALL(if (!buffer)
			{
				Internal_Log::LogWarning("Texture with path \"%\" couldn't be loaded. Check if the filepath is correct and the file isn't corrupted.", src.FullPath());
				return;
			})

			std::string outPath = s_AssetDirectory.String();
			outPath += dst.String();
			outPath += src.GetFilename().GetName();
			outPath += '.';
			outPath += PT_TEXTURE_EXT;

			std::ofstream stream(outPath, std::ios::binary);
			Graphics::TextureAPI::Settings settings;
			Math::Vec2u size((uint32_t)width, (uint32_t)height);
			stream.write((const char*)&settings, sizeof(Graphics::TextureAPI::Settings));
			stream.write((const char*)&size, sizeof(Math::Vec2u));
			stream.write((const char*)buffer, (size_t)size.x * (size_t)size.y * 4);
			stream.close();
			delete[] buffer;
		}
		else
		{
			Internal_Log::LogWarning("Src extension in \"%\" isn't supported! Supported formats are \"jpg\" and \"png\"", src.GetFilename().String());
		}
	}
}