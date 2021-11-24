#include "Ptpch.hpp"
#include "PtScene.hpp"
#include "Debug/InternalLog.hpp"
#include "Assets/AssetManager.hpp"
#include "Utils/FileRead.hpp"
#include "Core/LogMessages.hpp"

namespace Parrot
{
	PtScene::PtScene(const Utils::Filepath& filepath)
		: PtObj(PtObjType::Scene), m_Filepath(filepath)
	{
		std::ifstream stream(filepath.GetFullPath());
		InternalLog::LogAssert(stream.is_open(), StreamNotOpenErrorMsg, filepath.GetFullPath());

		std::string line;
		std::string key;
		std::string arg;
		std::getline(stream, line);
		Utils::GetArg(line, arg);
		m_Data.objCount = std::stoull(arg);
		m_Data.objs = new PtSceneObj[m_Data.objCount];
		int32_t index = -1;
		while (std::getline(stream, line))
		{
			Utils::GetKey(line, key);

			if (line.find("//") != line.npos)
				line = line.substr(0, line.find("//"));
			if (key == "SceneObject")
			{
				Utils::GetArg(line, arg);
				index++;
				if (index >= m_Data.objCount) return;
				m_Data.objs[index].tag = arg;
			}
			else if (key == "Transform")
			{
				if (Utils::GetArgWIdentifier(line, "Position", arg))
					m_Data.objs[index].transform.pos = Utils::ArgToVec3f(arg);
				if (Utils::GetArgWIdentifier(line, "Rotation", arg))
					m_Data.objs[index].transform.rot = Utils::ArgToVec3f(arg) * Math::PI / 180.0f;
				if (Utils::GetArgWIdentifier(line, "Scale", arg))
					m_Data.objs[index].transform.scale = Utils::ArgToVec3f(arg);
			}
			else if (key == "Camera")
			{
				float foV = Math::PI_HALFS;
				if (Utils::GetArgWIdentifier(line, "FoV", arg))
					foV = Utils::ArgToFloat(arg) * Math::PI / 180.0f;
				if (Utils::GetArgWIdentifier(line, "ZRange", arg))
					m_Data.objs[index].components[ComponentType::Camera] = new Camera(m_Data.objs[index].transform, foV, Utils::ArgToVec2f(arg));
				else
					m_Data.objs[index].components[ComponentType::Camera] = new Camera(m_Data.objs[index].transform, foV, Math::Vec2f(0.1f, 1000.0f));
			}
			else if (key ==  "Renderobject")
			{
				Utils::GetArgWIdentifier(line, "Mesh", arg);
				Utils::Filename mesh(arg);
				if (!AssetManager::IsAssetLoaded(mesh))
					AssetManager::LoadAsset(mesh);

				const PtShader* shader;
				if (!Utils::GetArgWIdentifier(line, "Shader", arg))
					shader = &AssetManager::GetShaderAsset("Default");
				else
				{
					Utils::Filename shaderName = arg;
					if (!AssetManager::IsAssetLoaded(shaderName))
						AssetManager::LoadAsset(shaderName);
					shader = &AssetManager::GetShaderAsset(shaderName);
				}

				const PtTex* tex;
				if (!Utils::GetArgWIdentifier(line, "Tex", arg))
					tex = &AssetManager::GetTextureAsset("NoTex");
				else
				{
					Utils::Filename texName = arg;
					if (!AssetManager::IsAssetLoaded(texName))
						AssetManager::LoadAsset(texName);
					tex = &AssetManager::GetTextureAsset(texName);
				}
				m_Data.objs[index].components[ComponentType::Renderobj] = new Renderobj(AssetManager::GetMeshAsset(mesh), *shader, *tex);
			}
			else if (key == "Script")
			{
				Utils::GetArg(line, arg);
				m_Data.objs[index].scripts.push_back(arg);
			}
		}
		stream.close();
	}
	const Utils::Filepath& PtScene::GetFilepath() const
	{
		return m_Filepath;
	}

	const PtScene::Data& PtScene::GetData() const
	{
		return m_Data;
	}
}