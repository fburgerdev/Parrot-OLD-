#include "Ptpch.hpp"
#include "AssetManager.hpp"
#include "Debug/Debugstream.hpp"
#include "Utils/Folder.hpp"

#include "DefaultAssets.hpp"
#include "Core/Constructor.hpp"

#include "Vendor/STB/stb_image.h"

using namespace Parrot::Asset;
namespace Parrot
{
	static constexpr const char* PT_MESH_EXT = ".MSH";
	static constexpr const char* PT_SHADER_EXT = ".SHDR";
	static constexpr const char* PT_TEX_EXT = ".TXTR";
	static constexpr const char* PT_SCENE_EXT = ".SCN";
	static constexpr const char* PT_SCENEOBJ_EXT = ".SCNOBJ";
	static constexpr const char* PT_WINDOW_EXT = ".WNDW";

	static Utils::Directory s_AssetDir;
	static std::unordered_map<Utils::Filename, Utils::Filepath> s_FilenameToFilepath;

	static std::unordered_map<std::string, Asset::TexAsset*> s_TexAssets;
	static std::unordered_map<std::string, Asset::ShaderAsset*> s_ShaderAssets;
	static std::unordered_map<std::string, Asset::MeshAsset*> s_MeshAssets;
	static std::unordered_map<std::string, Asset::WindowAsset*> s_WindowAssets;
	static std::unordered_map<std::string, Asset::SceneAsset*> s_SceneAssets;
	static std::unordered_map<std::string, Asset::SceneObjAsset*> s_SceneObjAssets;

	const Utils::Directory& AssetManager::GetAssetDir()
	{
		return s_AssetDir;
	}

	Asset::MeshAsset& AssetManager::CreateMeshAsset(const std::string& tag)
	{
		Asset::MeshAsset& asset = Constructor::MeshAssetConstructor(tag);
		s_MeshAssets[tag] = &asset;
		return asset;
	}
	Asset::TexAsset& AssetManager::CreateTexAsset(const std::string& tag)
	{
		Asset::TexAsset& asset = Constructor::TexAssetConstructor(tag);
		s_TexAssets[tag] = &asset;
		return asset;
	}

	Asset::MeshAsset& AssetManager::GetMeshAsset(const std::string& tag)
	{
		Asset::MeshAsset* asset;
		if (s_MeshAssets.find(tag) == s_MeshAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_MESH_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "MeshAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::MeshAssetConstructor(s_FilenameToFilepath[tag + PT_MESH_EXT]);
			s_MeshAssets[tag] = asset;
		}
		else
			asset = s_MeshAssets[tag];
		return *asset;
	}
	Asset::SceneAsset& AssetManager::GetSceneAsset(const std::string& tag)
	{
		Asset::SceneAsset* asset;
		if (s_SceneAssets.find(tag) == s_SceneAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_SCENE_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "SceneAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::SceneAssetConstructor(s_FilenameToFilepath[tag + PT_SCENE_EXT]);
			s_SceneAssets[tag] = asset;
		}
		else
			asset = s_SceneAssets[tag];
		return *asset;
	}
	Asset::SceneObjAsset& AssetManager::GetSceneObjAsset(const std::string& tag)
	{
		Asset::SceneObjAsset* asset;
		if (s_SceneObjAssets.find(tag) == s_SceneObjAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_SCENEOBJ_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "SceneObjAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::SceneObjAssetConstructor(s_FilenameToFilepath[tag + PT_SCENEOBJ_EXT]);
			s_SceneObjAssets[tag] = asset;
		}
		else
			asset = s_SceneObjAssets[tag];
		return *asset;
	}
	Asset::ShaderAsset& AssetManager::GetShaderAsset(const std::string& tag)
	{
		Asset::ShaderAsset* asset;
		if (s_ShaderAssets.find(tag) == s_ShaderAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_SHADER_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "ShaderAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::ShaderAssetConstructor(s_FilenameToFilepath[tag + PT_SHADER_EXT]);
			s_ShaderAssets[tag] = asset;
		}
		else
			asset = s_ShaderAssets[tag];
		return *asset;
	}
	Asset::TexAsset& AssetManager::GetTexAsset(const std::string& tag)
	{
		Asset::TexAsset* asset;
		if (s_TexAssets.find(tag) == s_TexAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_TEX_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "TexAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::TexAssetConstructor(s_FilenameToFilepath[tag + PT_TEX_EXT]);
			s_TexAssets[tag] = asset;
		}
		else
			asset = s_TexAssets[tag];
		return *asset;
	}
	Asset::WindowAsset& AssetManager::GetWindowAsset(const std::string& tag)
	{
		Asset::WindowAsset* asset;
		if (s_WindowAssets.find(tag) == s_WindowAssets.end())
		{
			if (PT_FUNC_GUARDS_ENABLED && s_FilenameToFilepath.find(tag + PT_WINDOW_EXT) == s_FilenameToFilepath.end())
			{
				DebugOut << AssetManagerLookupError << "WindowAsset: " << tag << Debugstream::EndMsg;
			}
			asset = &Constructor::WindowAssetConstructor(s_FilenameToFilepath[tag + PT_WINDOW_EXT]);
			s_WindowAssets[tag] = asset;
		}
		else
			asset = s_WindowAssets[tag];
		return *asset;
	}

	const Asset::MeshAsset& AssetManager::GetQuadMesh()
	{
		return *Asset::g_QuadMesh;
	}
	const Asset::MeshAsset& AssetManager::GetCubeMesh()
	{
		return *Asset::g_CubeMesh;
	}
	const Asset::TexAsset& AssetManager::GetDefaultTex()
	{
		return *Asset::g_DefaultTex;
	}
	const Asset::ShaderAsset& AssetManager::GetDefaultShader()
	{
		return *Asset::g_DefaultShader;
	}

	void Internal_SetAssetFolder(const Utils::Folder& folder)
	{
		s_AssetDir = folder.GetDir();
		for (Utils::Filepath filepath : folder)
			s_FilenameToFilepath[filepath.GetFilename()] = filepath;
	}
	void Internal_LoadImageFromFilename(const Utils::Filename& filename, Math::Vec2u& size, Math::Vec4u8*& buffer)
	{
		if (filename.GetExt() == "png" || filename.GetExt() == "jpg")
		{
			int32_t colorChannels = 4;
			stbi_set_flip_vertically_on_load(true);
			int32_t width, height, BPP;
			buffer = (Math::Vec4u8*)stbi_load(s_FilenameToFilepath[filename].FullPath().c_str(), &width, &height, &BPP, colorChannels);
			size.x = width;
			size.y = height;
			if (PT_FUNC_GUARDS_ENABLED && !buffer)
				DebugOut << ImageLoadWarning << filename << Debugstream::EndMsg;
		}
		else if (PT_FUNC_GUARDS_ENABLED)
			DebugOut << ImageLoadWarning << filename << Debugstream::EndMsg;
	}
}