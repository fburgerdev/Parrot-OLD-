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
			SceneObjAsset() : PtObj(PtObj::Type::SceneObjAsset) {}
		public:
			std::string tag;
			Component::Transform transform;
			std::unordered_map<ComponentType, void*> components;
			std::vector<Component::Script*(*)(SceneObj*)> scripts;
		};
	}
}