#pragma once
#include "SceneObject.hpp"

namespace Parrot
{
	class Scene
	{
	public:
		Scene(const std::string& tag);
		virtual ~Scene();

		const std::string& GetTag() const;

		void AddSceneObject(SceneObject& sceneObject);
		SceneObject& GetSceneObject(const std::string& tag);

		void UpdateObjs();
		void Render();
	private:
		std::string m_Tag;
		std::unordered_map<std::string, SceneObject*> m_SceneObjs;
	};
}