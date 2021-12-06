#include "Ptpch.hpp"
#include "SceneObjAsset.hpp"

#include "Utils/FileRead.hpp"
#include "Debug/Internal_Log.hpp"
#include "Assets/Internal_AssetManager.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	namespace Asset
	{
		static void CreateSceneObjAsset(std::ifstream& stream, SceneObjAsset& obj)
		{
			std::string line;
			std::string key;
			std::string arg;
			bool sceneObjNamed = false;
			while (std::getline(stream, line))
			{
				Utils::GetKey(line, key);

				if (line.find("//") != line.npos)
					line = line.substr(0, line.find("//"));
				if (key == "SceneObj")
				{
					if (sceneObjNamed)
					{
						// go back to last line
						stream.seekg(-(int64_t)line.length() - 2, std::ios::cur);
						return;
					}
					Utils::GetArg(line, arg);
					obj.tag = arg;
					sceneObjNamed = true;
				}
				else if (key == "Transform")
				{
					if (Utils::GetArgWIdentifier(line, "Position", arg))
						obj.transform.pos = Utils::ArgToVec3f(arg);
					if (Utils::GetArgWIdentifier(line, "Rotation", arg))
						obj.transform.rot = Utils::ArgToVec3f(arg) * Math::PI / 180.0f;
					if (Utils::GetArgWIdentifier(line, "Scale", arg))
						obj.transform.scale = Utils::ArgToVec3f(arg);
				}
				else if (key == "Camera")
				{
					float foV = Math::PI_HALFS;
					if (Utils::GetArgWIdentifier(line, "FoV", arg))
						foV = Utils::ArgToFloat(arg) * Math::PI / 180.0f;
					Math::Vec2f zRange(0.1f, 1000.0f);
					if (Utils::GetArgWIdentifier(line, "ZRange", arg))
						zRange = Utils::ArgToVec2f(arg);
					obj.components[ComponentType::Camera] = new Component::Camera(obj.transform, foV, zRange);
				}
				else if (key == "RenderObj")
				{
					const MeshAsset* mesh;
					Utils::GetArgWIdentifier(line, "Mesh", arg);
					if (arg == "Quad")
						mesh = &AssetManager::GetQuadMesh();
					else if (arg == "Cube")
						mesh = &AssetManager::GetCubeMesh();
					else
					{
						Utils::Filename meshFilename(arg);
						if (!AssetManager::IsAssetLoaded(meshFilename))
							mesh = &AssetManager::LoadMeshAsset(meshFilename);
						else
							mesh = &AssetManager::GetMeshAsset(meshFilename);
					}

					const ShaderAsset* shader;
					if (!Utils::GetArgWIdentifier(line, "Shader", arg))
						shader = &AssetManager::GetStandardShader();
					else
					{
						Utils::Filename shaderFilename = arg;
						if (!AssetManager::IsAssetLoaded(shaderFilename))
							shader = &AssetManager::LoadShaderAsset(shaderFilename);
						else
							shader = &AssetManager::GetShaderAsset(shaderFilename);
					}

					const TexAsset* tex;
					if (!Utils::GetArgWIdentifier(line, "Tex", arg))
						tex = &AssetManager::GetWhiteTex();
					else
					{
						Utils::Filename texFilename = arg;
						if (!AssetManager::IsAssetLoaded(texFilename))
							tex = &AssetManager::LoadTexAsset(texFilename);
						else
							tex = &AssetManager::GetTexAsset(texFilename);
					}
					obj.components[ComponentType::RenderObj] = new Component::RenderObj(*mesh, *shader, *tex);
				}
				else if (key == "Script")
				{
					Utils::GetArg(line, arg);
					obj.scripts.push_back(Internal_Application::GetScriptCreationFunc(arg));
				}
				else if (key == "Light")
				{
					Math::Vec3f dir(0, -1, 0);
					if (Utils::GetArgWIdentifier(line, "Dir", arg))
						dir = Utils::ArgToVec3f(arg);
					Math::Vec3u8 color(255);
					if (Utils::GetArgWIdentifier(line, "Color", arg))
						color = Utils::ArgToVec3u8(arg);
					float intensity = 1.0f;
					if (Utils::GetArgWIdentifier(line, "Intensity", arg))
						intensity = Utils::ArgToFloat(arg);
					obj.components[ComponentType::Light] = new Component::Light(dir, color, intensity);
				}
			}
		}

		SceneObjAsset::SceneObjAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::SceneObjAsset)
		{
			std::ifstream stream(filepath.FullPath());
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
		
			CreateSceneObjAsset(stream, *this);
			stream.close();
		}

		SceneObjAsset::SceneObjAsset(std::ifstream& stream)
			: PtObj(PtObj::Type::SceneObjAsset)
		{
			CreateSceneObjAsset(stream, *this);
		}
	}
}