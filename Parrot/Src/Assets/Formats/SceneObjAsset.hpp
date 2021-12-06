#pragma once
#include "Scene/Components.hpp"
#include "SceneAsset.hpp"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

namespace Parrot
{
	namespace Asset
	{
		class SceneObjAsset : public PtObj
		{
		public:
			SceneObjAsset(const Utils::Filepath& filepath);
		private:
			SceneObjAsset(std::ifstream& stream);
		public:
			std::string tag;
			Component::Transform transform;
			std::unordered_map<ComponentType, void*> components;
			std::vector<Component::Script*(*)(SceneObj*)> scripts;
		private:
			friend SceneAsset;
		};
	}
}