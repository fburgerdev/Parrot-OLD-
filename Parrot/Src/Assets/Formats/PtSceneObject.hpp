#pragma once
#include <unordered_map>
#include <string>
#include "ClientInterface/Scene/Components.hpp"

namespace Parrot
{
	enum class ComponentType
	{
		None = 0, Transform, Renderobject, Camera
	};

	class PtSceneObject
	{
	public:
		std::string tag;
		Transform transform;
		std::unordered_map<ComponentType, void*> components;
		std::vector<std::string> scripts;
	};
}