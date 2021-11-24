#pragma once
#include <string>
#include <unordered_map>
#include "Components.hpp"
#include "Assets/Formats/PtSceneObj.hpp"

namespace Parrot
{	
	class Scene;
	class SceneObj : public PtObj
	{
	public:
		SceneObj(Scene& scene, const PtSceneObj& ptSceneObj);
		~SceneObj();

		const std::string& GetTag() const;
		Scene& GetScene();

		bool HasComponent(ComponentType type);
		template<class _Type, class... _Args>
		_Type& AddComponent(const _Args&... args);
		template<class _Type>
		_Type& GetComponent();

		std::unordered_map<std::string, Script*>& GetScripts();
	public:
		Transform transform;
	private:
		std::string m_Tag;
		Scene& m_Scene;
		std::unordered_map<ComponentType, void*> m_Components;
		std::unordered_map<std::string, Script*> m_Scripts;
	};
}