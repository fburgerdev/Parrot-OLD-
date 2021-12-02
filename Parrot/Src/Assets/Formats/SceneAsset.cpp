#include "Ptpch.hpp"
#include "SceneAsset.hpp"

#include "Utils/FileRead.hpp"
#include "Debug/Internal_Log.hpp"
#include "Assets/Internal_AssetManager.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	namespace Asset
	{
		SceneAsset::SceneAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::Scene), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath());
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());

			std::string line;
			std::string key;
			std::string arg;

			std::getline(stream, line);
			Utils::GetArg(line, arg);
			objCount = std::stoull(arg);
			objs = new SceneObjAsset[objCount];
			
			int32_t index = -1;
			while (std::getline(stream, line))
			{
				Utils::GetKey(line, key);

				if (line.find("//") != line.npos)
					line = line.substr(0, line.find("//"));
				if (key == "SceneObject")
				{
					Utils::GetArg(line, arg);
					if (++index >= objCount) return;
					objs[index].tag = arg;
				}
				else if (key == "Transform")
				{
					if (Utils::GetArgWIdentifier(line, "Position", arg))
						objs[index].transform.pos = Utils::ArgToVec3f(arg);
					if (Utils::GetArgWIdentifier(line, "Rotation", arg))
						objs[index].transform.rot = Utils::ArgToVec3f(arg) * Math::PI / 180.0f;
					if (Utils::GetArgWIdentifier(line, "Scale", arg))
						objs[index].transform.scale = Utils::ArgToVec3f(arg);
				}
				else if (key == "Camera")
				{
					float foV = Math::PI_HALFS;
					if (Utils::GetArgWIdentifier(line, "FoV", arg))
						foV = Utils::ArgToFloat(arg) * Math::PI / 180.0f;
					Math::Vec2f zRange(0.1f, 1000.0f);
					if (Utils::GetArgWIdentifier(line, "ZRange", arg))
						zRange = Utils::ArgToVec2f(arg);
					objs[index].components[ComponentType::Camera] = new Component::Camera(objs[index].transform, foV, zRange);
				}
				else if (key == "Renderobject")
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
							AssetManager::LoadAsset(meshFilename);
						mesh = &AssetManager::GetMeshAsset(meshFilename);
					}

					const ShaderAsset* shader;
					if (!Utils::GetArgWIdentifier(line, "Shader", arg))
						shader = &AssetManager::GetStandardShader();
					else
					{
						Utils::Filename shaderFilename = arg;
						if (!AssetManager::IsAssetLoaded(shaderFilename))
							AssetManager::LoadAsset(shaderFilename);
						shader = &AssetManager::GetShaderAsset(shaderFilename);
					}

					const TexAsset* tex;
					if (!Utils::GetArgWIdentifier(line, "Tex", arg))
						tex = &AssetManager::GetWhiteTex();
					else
					{
						Utils::Filename texFilename = arg;
						if (!AssetManager::IsAssetLoaded(texFilename))
							AssetManager::LoadAsset(texFilename);
						tex = &AssetManager::GetTexAsset(texFilename);
					}
					objs[index].components[ComponentType::Renderobj] = new Component::Renderobj(*mesh, *shader, *tex);
				}
				else if (key == "Script")
				{
					Utils::GetArg(line, arg);
					objs[index].scripts.push_back(Internal_Application::GetScriptCreationFunc(arg));
				}
			}
			stream.close();
		}
	}
}