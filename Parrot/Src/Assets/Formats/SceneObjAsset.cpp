#include "Ptpch.hpp"
#include "SceneObjAsset.hpp"
#include "Debug/Debugstream.hpp"
#include "Assets/AssetRead.hpp"
#include "Assets/AssetManager.hpp"

namespace Parrot
{
	ScriptCreationFunc Internal_GetScriptCreationFunc(const std::string& tag);
	namespace Asset
	{
		std::string SceneObjAsset::ExtractSceneObjAsset(Utils::FileIn& stream, SceneObjAsset& obj)
		{
			std::string assertMsg = "SceneObjAsset Syntax Error in " + stream.GetFilepath().FullPath();

			std::string tag;

			std::string line;
			std::string key;
			std::string arg;

			std::streampos cursorPos = stream.tellg();
			while (std::getline(stream, line))
			{
				AssetSyntaxAssert(GetKey(line, key), assertMsg);

				size_t commentStart = line.find("//");
				if (commentStart != line.npos)
					line = line.substr(0, commentStart);
				if (key == "sceneobj")
				{
					if (!tag.empty())
					{
						stream.seekg(cursorPos);
						return tag;
					}
					AssetSyntaxAssert(GetArg(line, arg), assertMsg);
					tag = arg;
				}
				else if (key == "transform")
				{
					if (GetArgWIdentifier(line, "Position", arg))
						AssetSyntaxAssert(ArgToVec3f(arg, obj.transform.pos), assertMsg);
					if (GetArgWIdentifier(line, "Rotation", arg))
					{
						AssetSyntaxAssert(ArgToVec3f(arg, obj.transform.rot), assertMsg);
						obj.transform.rot *= Math::PI / 180.0f;
					}
					if (GetArgWIdentifier(line, "Scale", arg))
						AssetSyntaxAssert(ArgToVec3f(arg, obj.transform.scale), assertMsg);
				}
				else if (key == "camera")
				{
					float foV = Math::PI_HALFS;
					if (GetArgWIdentifier(line, "Fov", arg))
						foV = ArgToFloat(arg) * Math::PI / 180.0f;
					Math::Vec2f zRange(0.1f, 1000.0f);
					if (GetArgWIdentifier(line, "Zrange", arg))
						AssetSyntaxAssert(ArgToVec2f(arg, zRange), assertMsg);
					obj.components[ComponentType::Camera] = new Component::Camera(obj.transform, foV, zRange);
				}
				else if (key == "renderobj")
				{
					const MeshAsset* mesh;
					GetArgWIdentifier(line, "Mesh", arg);
					if (arg == "Quad")
						mesh = &AssetManager::GetQuadMesh();
					else if (arg == "Cube")
						mesh = &AssetManager::GetCubeMesh();
					else
						mesh = &AssetManager::GetMeshAsset(arg);

					const ShaderAsset* shader;
					if (!GetArgWIdentifier(line, "Shader", arg))
						shader = &AssetManager::GetDefaultShader();
					else
						shader = &AssetManager::GetShaderAsset(arg);

					const TexAsset* tex;
					if (!GetArgWIdentifier(line, "Tex", arg))
						tex = &AssetManager::GetDefaultTex();
					else
						tex = &AssetManager::GetTexAsset(arg);
					obj.components[ComponentType::RenderObj] = new Component::RenderObj(*mesh, *tex, *shader);
				}
				else if (key == "script")
				{
					GetArg(line, arg);
					obj.scripts.push_back(Internal_GetScriptCreationFunc(arg));
				}
				else if (key == "light")
				{
					Math::Vec3f dir(0, -1, 0);
					if (GetArgWIdentifier(line, "Dir", arg))
						AssetSyntaxAssert(ArgToVec3f(arg, dir), assertMsg);
					Math::Vec3u8 color(255);
					if (GetArgWIdentifier(line, "Color", arg))
						AssetSyntaxAssert(ArgToVec3u8(arg, color), assertMsg);
					float intensity = 1.0f;
					if (GetArgWIdentifier(line, "Intensity", arg))
						intensity = ArgToFloat(arg);
					obj.components[ComponentType::Light] = new Component::Light(dir, color, intensity);
				}
				cursorPos = stream.tellg();
			}
			return tag;
		}

		SceneObjAsset::SceneObjAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName())
		{
			Utils::FileIn stream(filepath);
			if (!stream.is_open())
				return;
			ExtractSceneObjAsset(stream, *this);
			stream.close();
		}

		SceneObjAsset::SceneObjAsset(Utils::FileIn& stream)
			: PtObj()
		{
			m_Tag = ExtractSceneObjAsset(stream, *this);
		}
	}
}