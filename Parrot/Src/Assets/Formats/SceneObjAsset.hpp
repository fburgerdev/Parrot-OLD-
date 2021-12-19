#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Utils/Filestream.hpp"
#include "Scene/Components.hpp"

#include <vector>
#include <unordered_map>
#include <fstream>

namespace Parrot
{
	typedef Component::Script* (*ScriptCreationFunc)(SceneObj*);
	class Constructor;
	namespace Asset
	{
		class SceneObjAsset : public PtObj
		{
		private:
			SceneObjAsset(const Utils::Filepath& filepath);
			SceneObjAsset(Utils::FileIn& stream);
			friend Constructor;
		private:
			static std::string ExtractSceneObjAsset(Utils::FileIn& stream, SceneObjAsset& obj);
		public:
			Component::Transform transform;
			std::unordered_map<ComponentType, void*> components;
			std::vector<ScriptCreationFunc> scripts;
		};
	}
}