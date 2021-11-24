#include "Ptpch.hpp"
#include "AssetManager.hpp"
#include "InternalAssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"

#include "Vendor/STB/stb_image.h"

#define PT_MESH_EXT "MSH"
#define PT_SHADER_EXT "SHDR"
#define PT_TEXTURE_EXT "TXTR"
#define PT_SCENE_EXT "SCN"
#define PT_WINDOW_EXT "WNDW"
#define PT_EXT_LIST "MSH, SHDR, TXTR, SCN, WNDW"

namespace Parrot
{
	namespace AssetManager
	{
		static Utils::Directory s_AssetDirectory("");
		static std::unordered_map<std::string, std::string> s_FilenameToPath;
		static std::unordered_map<std::string, void*> s_LoadedAssets;

		Format GetFormatFromExtension(std::string_view ext)
		{
			if (ext == PT_MESH_EXT)
				return Format::Mesh;
			else if (ext == PT_SHADER_EXT)
				return Format::Shader;
			else if (ext == PT_TEXTURE_EXT)
				return Format::Texture;
			else if (ext == PT_SCENE_EXT)
				return Format::Scene;
			else if (ext == PT_WINDOW_EXT)
				return Format::Window;
			return Format::Unknown;
		}

		const Utils::Directory& GetAssetDir()
		{
			return s_AssetDirectory;
		}

		bool LoadAsset(const Utils::Filename& filename)
		{
			Format format = GetFormatFromExtension(filename.GetExtension());
			PT_GUARD_CALL(
			if (format == Format::Unknown)
			{
				InternalLog::LogWarning("Trying to load asset of unknown format \"%\"! Try using one of these formats \"%\"", filename.GetExtension(), PT_EXT_LIST);
				return false;
			}
			if (s_FilenameToPath.find(filename.String()) == s_FilenameToPath.end())
			{
				InternalLog::LogWarning("Asset \"%\" wasn't found in asset directory \"%\"!", filename.String(), s_AssetDirectory.String());
				return false;
			}
			if (s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end())
			{
				InternalLog::LogWarning("Asset \"%\" was already loaded!", filename.String());
				return false;
			})

			switch (format)
			{
			case Format::Mesh:
				s_LoadedAssets[filename.String()] = new PtMesh(s_FilenameToPath[filename.String()]);
				return true;
			case Format::Shader:
				s_LoadedAssets[filename.String()] = new PtShader(s_FilenameToPath[filename.String()]);
				return true;
			case Format::Texture:
				s_LoadedAssets[filename.String()] = new PtTex(s_FilenameToPath[filename.String()]);
				return true;
			case Format::Scene:
				s_LoadedAssets[filename.String()] = new PtScene(s_FilenameToPath[filename.String()]);
				return true;
			case Format::Window:
				s_LoadedAssets[filename.String()] = new PtWindow(s_FilenameToPath[filename.String()]);
				return true;
			default:
				return false;
			}
			return false;
		}
		bool IsAssetLoaded(const Utils::Filename& filename)
		{
			return s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end();
		}
		void UnloadAsset(const Utils::Filename& filename)
		{
			PT_GUARD_CALL(if (s_LoadedAssets.find(filename.String()) == s_LoadedAssets.end())
			{
				InternalLog::LogWarning("Asset \"%\" is not loaded!", filename.String());
				return;
			})
			delete s_LoadedAssets[filename.String()];
			s_LoadedAssets.erase(filename.String());
		}

		PtTex& GetTextureAsset(const std::string& name)
		{
			std::string filename = name + '.' + PT_TEXTURE_EXT;
			InternalLog::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename);
			return *(PtTex*)s_LoadedAssets[filename];
		}
		PtShader& GetShaderAsset(const std::string& name)
		{
			std::string filename = name + '.' + PT_SHADER_EXT;
			InternalLog::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename);
			return *(PtShader*)s_LoadedAssets[filename];
		}
		PtMesh& GetMeshAsset(const std::string& name)
		{
			std::string filename = name + '.' + PT_MESH_EXT;
			InternalLog::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename);
			return *(PtMesh*)s_LoadedAssets[filename];
		}
		PtWindow& GetWindowAsset(const std::string& name)
		{
			std::string filename = name + '.' + PT_WINDOW_EXT;
			InternalLog::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename);
			return *(PtWindow*)s_LoadedAssets[filename];
		}
		PtScene& GetSceneAsset(const std::string& name)
		{
			std::string filename = name + '.' + PT_SCENE_EXT;
			InternalLog::LogAssert(s_LoadedAssets.find(filename) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename);
			return *(PtScene*)s_LoadedAssets[filename];
		}
		PtTex& GetTextureAsset(const Utils::Filename& filename)
		{
			InternalLog::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename.String());
			return *(PtTex*)s_LoadedAssets[filename.String()];
		}
		PtShader& GetShaderAsset(const Utils::Filename& filename)
		{
			InternalLog::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename.String());
			return *(PtShader*)s_LoadedAssets[filename.String()];
		}
		PtMesh& GetMeshAsset(const Utils::Filename& filename)
		{
			InternalLog::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename.String());
			return *(PtMesh*)s_LoadedAssets[filename.String()];
		}
		PtWindow& GetWindowAsset(const Utils::Filename& filename)
		{
			InternalLog::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename.String());
			return *(PtWindow*)s_LoadedAssets[filename.String()];
		}
		PtScene& GetSceneAsset(const Utils::Filename& filename)
		{
			InternalLog::LogAssert(s_LoadedAssets.find(filename.String()) != s_LoadedAssets.end(), AssetAccessingErrorMsg, filename.String());
			return *(PtScene*)s_LoadedAssets[filename.String()];
		}

		// maps all filenames in the asset directory to their actual location so we don't have to mess with filepaths later on
		void Internal_InitAssetDir(const Utils::Directory& assetDirectory)
		{
			s_AssetDirectory = assetDirectory;
			for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(assetDirectory.String()))
			{
				Utils::Filepath filepath(dirEntry.path().string());
				if (GetFormatFromExtension(filepath.GetFilename().GetExtension()) != Format::Unknown)
					s_FilenameToPath[filepath.GetFilename().String()] = std::move(filepath.GetFullPath());
			}
		}
		void Internal_LoadAllFromDir()
		{
			for (auto& pair : s_FilenameToPath)
			{
				Utils::Filename filename(pair.first);
				Format format = GetFormatFromExtension(filename.GetExtension());
				if (!IsAssetLoaded(filename))
					LoadAsset(filename);
			}
		}

		void Internal_ConvertToAsset(const Utils::Filepath& src, const Utils::Directory& dst)
		{
			std::string_view srcExt = src.GetFilename().GetExtension();
			if (srcExt == "png" || srcExt == "jpg")
			{
				int32_t colorChannels = 4;
				stbi_set_flip_vertically_on_load(true);
				int32_t width, height, BPP;
				uint8_t* buffer = stbi_load(src.GetFullPath().c_str(), &width, &height, &BPP, colorChannels);
				PT_GUARD_CALL(if (!buffer)
				{
					InternalLog::LogWarning("Texture with path \"%\" couldn't be loaded. Check if the filepath is correct and the file isn't corrupted.", src.GetFullPath());
					return;
				})

				std::string outPath = s_AssetDirectory.String();
				outPath += dst.String();
				outPath += src.GetFilename().GetName();
				outPath += '.';
				outPath += PT_TEXTURE_EXT;

				std::ofstream stream(outPath, std::ios::binary);
				TextureAPI::Settings settings;
				Math::Vec2u size((uint32_t)width, (uint32_t)height);
				stream.write((const char*)&settings, sizeof(TextureAPI::Settings));
				stream.write((const char*)&size, sizeof(Math::Vec2u));
				stream.write((const char*)buffer, (size_t)size.x * (size_t)size.y * 4);
				stream.close();
				delete[] buffer;
			}
			/*	else if (srcExt == "GLSL")
			{
				PT_GUARD_CALL(if (dstExt != PT_SHADER_EXT)
				{
					InternalLog::LogWarning("Asset conversion \"%\"->\"%\" failed, because the src format doesn't match the dst format! Use the dst format \".%\" to create shaders.", src.GetFilename().String(), PT_SHADER_EXT, dst.GetFilename().String());
					return;
				})
				std::ifstream ifstream(src.GetFullPath(), std::ios::binary);
				std::ofstream ofstream(dst.GetFullPath(), std::ios::binary);
				ofstream << ifstream.rdbuf();
				ifstream.close();
				ofstream.close();
			}*/
			else
			{
				InternalLog::LogWarning("Src extension in \"%\" isn't supported! Supported formats are \"jpg\", \"png\" and \"GLSL\"", src.GetFilename().String());
			}
		}

		//void ConvertToAssetIfNExist(const Utils::Filepath& src, const Utils::Filepath& dst)
		//{
		//	if (std::filesystem::exists(dst.GetFullPath()))
		//		return;
		//	ConvertToAsset(src, dst);
		//}
	}
}