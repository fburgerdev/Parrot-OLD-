#pragma once
#include <unordered_map>
#include "Assets/Formats/PtScene.hpp"
#include "SceneObject.hpp"

namespace Parrot
{
	class Window;
	class Scene
	{
	public:
		Scene(Window& window, const PtScene& ptScene);
		~Scene();

		const std::string& GetTag() const;
		Window& GetWindow();

		//void AddSceneObject(SceneObject& sceneObject);
		bool ContainsSceneObject(const std::string& tag);
		SceneObject& GetSceneObject(const std::string& tag);

		void UpdateObjs();
		void Render();
		void HandleEvent(Event e);
	private:
		std::string m_Tag;
		Window& m_Window;
		std::unordered_map<std::string, SceneObject*> m_SceneObjs;
	};
}