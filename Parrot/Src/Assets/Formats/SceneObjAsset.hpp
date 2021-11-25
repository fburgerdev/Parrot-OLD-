#pragma once
#include <unordered_map>
#include "Scene/Components.hpp"

namespace Parrot
{
	namespace Asset
	{
		class SceneObjAsset : public PtObj
		{
		public:
			SceneObjAsset() : PtObj(PtObjType::SceneObjAsset) {}

			std::string tag;
			Component::Transform transform;
			std::unordered_map<ComponentType, void*> components;
			std::vector<std::string> scripts;
		};
	}
}