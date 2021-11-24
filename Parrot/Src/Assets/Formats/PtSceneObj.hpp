#pragma once
#include <unordered_map>
#include <string>
#include "Scene/Components.hpp"

namespace Parrot
{
	enum class ComponentType
	{
		None = 0, Transform, Renderobj, Camera
	};

	class PtSceneObj : public PtObj
	{
	public:
		PtSceneObj() : PtObj(PtObjType::PtSceneObj) {}

		std::string tag;
		Transform transform;
		std::unordered_map<ComponentType, void*> components;
		std::vector<std::string> scripts;
	};
}