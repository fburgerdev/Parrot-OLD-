#include "Ptpch.hpp"
#include "AssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "Vendor/STB/stb_image.h"

namespace Parrot
{
	#define PT_MESH_EXT "MSH"
	#define PT_SHADER_EXT "SHDR"
	#define PT_TEXTURE_EXT "TXTR"
	#define PT_WINDOW_EXT "WNDW"
	#define PT_SCENE_EXT "SCN"

	void AssetManager::ConvertToAsset(const Utils::Filepath& src, const Utils::Filepath& dst)
	{
		if (src.Extension() == "png" || src.Extension() == "jpg")
		{
			PT_GUARD_CALL(if (dst.Extension() != PT_TEXTURE_EXT)
			{
				InternalLog::LogWarning("Asset creation \"%\"->\"%\" failed, because the src format doesn't match the dst format! Use the dst format \".%\" to create textures.", src.Filename(), PT_TEXTURE_EXT, dst.Filename());
				return;
			})
			int32_t colorChannels = 4;
			stbi_set_flip_vertically_on_load(true);
			int32_t width, height, BPP;
			uint8_t* buffer = stbi_load(src.FullPath().c_str(), &width, &height, &BPP, colorChannels);
			PT_GUARD_CALL(if (!buffer)
			{
				InternalLog::LogWarning("Texture with path \"%\" couldn't be loaded. Check if the filepath is correct and the file isn't corrupted.", src.FullPath());
				return;
			})

			std::ofstream stream(dst.FullPath(), std::ios::binary);
			PtTex::Settings settings;
			Math::Vec2u size((uint32_t)width, (uint32_t)height);
			stream.write((const char*)&settings, sizeof(PtTex::Settings));
			stream.write((const char*)&size, sizeof(Math::Vec2u));
			stream.write((const char*)buffer, (size_t)size.x * (size_t)size.y * 4);
			stream.close();
			delete[] buffer;
		}
		else if (src.Extension() == "GLSL")
		{
			PT_GUARD_CALL(if (dst.Extension() != PT_SHADER_EXT)
			{
				InternalLog::LogWarning("Asset creation \"%\"->\"%\" failed, because the src format doesn't match the dst format! Use the dst format \".%\" to create shaders.", src.Filename(), PT_SHADER_EXT, dst.Filename());
				return;
			})
			std::ifstream ifstream(src.FullPath(), std::ios::binary);
			std::ofstream ofstream(dst.FullPath(), std::ios::binary);
			ofstream << ifstream.rdbuf();
			ifstream.close();
			ofstream.close();
		}
		else
		{
			InternalLog::LogWarning("Src extension in \"%\" isn't supported!", src.Filename());
		}
	}

	void AssetManager::ConvertToAssetIfNExist(const Utils::Filepath& src, const Utils::Filepath& dst)
	{
		if (std::filesystem::exists(dst.FullPath()))
			return;
		ConvertToAsset(src, dst);
	}

	void AssetManager::LoadAsset(const Utils::Filepath& filepath)
	{
		const std::string& key = (const std::string)filepath.FilenameNExt();
		if (filepath.Extension() == PT_TEXTURE_EXT)
		{
			PT_GUARD_CALL(if (s_Textures.find(key) != s_Textures.end())
			{
				InternalLog::LogWarning("Asset \"%\" already loaded!", filepath.Filename());
				return;
			})
			s_Textures[key] = new PtTex(filepath);
		}
		else if (filepath.Extension() == PT_SHADER_EXT)
		{
			PT_GUARD_CALL(if (s_Shaders.find(key) != s_Shaders.end())
			{
				InternalLog::LogWarning("Asset \"%\" already loaded!", filepath.Filename());
				return;
			})
			s_Shaders[key] = new PtShader(filepath);
		}
		else if (filepath.Extension() == PT_MESH_EXT)
		{
			PT_GUARD_CALL(if (s_Meshes.find(key) != s_Meshes.end())
			{
				InternalLog::LogWarning("Asset \"%\" already loaded!", filepath.Filename());
				return;
			})
			s_Meshes[key] = new PtMesh(filepath);
		}
		else if (filepath.Extension() == PT_WINDOW_EXT)
		{
			PT_GUARD_CALL(if (s_Windows.find(key) != s_Windows.end())
			{
				InternalLog::LogWarning("Asset \"%\" already loaded!", filepath.Filename());
				return;
			})
			s_Windows[key] = new PtWindow(filepath);
		}
		else if (filepath.Extension() == PT_SCENE_EXT)
		{
			PT_GUARD_CALL(if (s_Scenes.find(key) != s_Scenes.end())
			{
				InternalLog::LogWarning("Asset \"%\" already loaded!", filepath.Filename());
				return;
			})
			s_Scenes[key] = new PtScene(filepath);
		}
		else
			InternalLog::LogWarning("Failed to load Asset! Extension in \"%\" isn't a supported Asset! Use \".%\", \".%\",\".%\", \".%\" or \".%\".", filepath.Filename(), PT_TEXTURE_EXT, PT_SHADER_EXT, PT_MESH_EXT, PT_WINDOW_EXT, PT_SCENE_EXT);
	}
	void AssetManager::UnloadAsset(const Utils::Filepath& filepath)
	{
		if (filepath.Extension() == PT_TEXTURE_EXT)
		{
			PT_GUARD_CALL(if (s_Textures.find((const std::string&)filepath.FilenameNExt()) == s_Textures.end())
			{
				InternalLog::LogWarning("Asset unload failed! Asset \"%\" is not loaded.", filepath.Filename());
				return;
			})
			delete s_Textures[std::string(filepath.FilenameNExt())];
			s_Textures.erase(std::string(filepath.FilenameNExt()));
		}
		else if (filepath.Extension() == PT_SHADER_EXT)
		{
			PT_GUARD_CALL(if (s_Shaders.find((const std::string&)filepath.FilenameNExt()) == s_Shaders.end())
			{
				InternalLog::LogWarning("Asset unload failed! Asset \"%\" is not loaded.", filepath.Filename());
				return;
			})
			delete s_Shaders[std::string(filepath.FilenameNExt())];
			s_Shaders.erase(std::string(filepath.FilenameNExt()));
		}
		else if (filepath.Extension() == PT_MESH_EXT)
		{
			PT_GUARD_CALL(if (s_Meshes.find((const std::string&)filepath.FilenameNExt()) == s_Meshes.end())
			{
				InternalLog::LogWarning("Asset unload failed! Asset \"%\" is not loaded.", filepath.Filename());
				return;
			})
			delete s_Meshes[std::string(filepath.FilenameNExt())];
			s_Meshes.erase(std::string(filepath.FilenameNExt()));
		}
		else if (filepath.Extension() == PT_WINDOW_EXT)
		{
			PT_GUARD_CALL(if (s_Windows.find((const std::string&)filepath.FilenameNExt()) == s_Windows.end())
			{
				InternalLog::LogWarning("Asset unload failed! Asset \"%\" is not loaded.", filepath.Filename());
				return;
			})
			delete s_Windows[std::string(filepath.FilenameNExt())];
			s_Windows.erase(std::string(filepath.FilenameNExt()));
		}
		else if (filepath.Extension() == PT_SCENE_EXT)
		{
			PT_GUARD_CALL(if (s_Scenes.find((const std::string&)filepath.FilenameNExt()) == s_Scenes.end())
			{
				InternalLog::LogWarning("Asset unload failed! Asset \"%\" is not loaded.", filepath.Filename());
				return;
			})
			delete s_Scenes[std::string(filepath.FilenameNExt())];
			s_Scenes.erase(std::string(filepath.FilenameNExt()));
		}
		else
			InternalLog::LogAssert(false, "Failed to unload Asset! Extension in \"%\" isn't a supported Asset! Use \".%\", \".%\",\".%\", \".%\" or \".%\".", filepath.Filename(), PT_TEXTURE_EXT, PT_SHADER_EXT, PT_MESH_EXT, PT_WINDOW_EXT, PT_SCENE_EXT);
	}
	const PtTex& AssetManager::GetTexture(const std::string& name)
	{
		InternalLog::LogAssert(s_Textures.find(name) != s_Textures.end(), "Could not find loaded Texture in AssetManager \"%\"", name);
		return *s_Textures[name];
	}
	const PtShader& AssetManager::GetShader(const std::string& name)
	{
		InternalLog::LogAssert(s_Shaders.find(name) != s_Shaders.end(), "Could not find loaded Shader in AssetManager \"%\"", name);
		return *s_Shaders[name];
	}
	const PtMesh& AssetManager::GetMesh(const std::string& name)
	{
		InternalLog::LogAssert(s_Meshes.find(name) != s_Meshes.end(), "Could not find loaded Mesh in AssetManager \"%\"", name);
		return *s_Meshes[name];
	}
	const PtWindow& AssetManager::GetWindow(const std::string& name)
	{
		InternalLog::LogAssert(s_Windows.find(name) != s_Windows.end(), "Could not find loaded Window in AssetManager \"%\"", name);
		return *s_Windows[name];
	}
	const PtScene& AssetManager::GetScene(const std::string& name)
	{
		InternalLog::LogAssert(s_Scenes.find(name) != s_Scenes.end(), "Could not find loaded Scene in AssetManager \"%\"", name);
		return *s_Scenes[name];
	}

	std::unordered_map<std::string, PtTex*> AssetManager::s_Textures;
	std::unordered_map<std::string, PtShader*> AssetManager::s_Shaders;
	std::unordered_map<std::string, PtMesh*> AssetManager::s_Meshes;
	std::unordered_map<std::string, PtWindow*> AssetManager::s_Windows;
	std::unordered_map<std::string, PtScene*> AssetManager::s_Scenes;
}