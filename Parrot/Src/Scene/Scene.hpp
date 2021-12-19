#pragma once
#include "Scene/SceneObj.hpp"

#include <unordered_map>

int main();
namespace Parrot
{
	class Window;
	class Scene : public PtObj
	{
	private:
		Scene(Window& window, const Asset::SceneAsset& asset);
		friend Window;
	public:
		~Scene();
		Window& GetWindow();

		SceneObj& AddSceneObj(const Asset::SceneObjAsset& asset);
		bool HasSceneObj(const std::string& tag);
		SceneObj& GetSceneObj(const std::string& tag);

		void RaiseEvent(Event e);
	private:
		void UpdateObjs();
		void Render();
	private:
		Window& m_Window;
		std::unordered_map<std::string, SceneObj*> m_SceneObjs;
		std::vector<Component::Script*> m_Scripts;
		bool m_OnCreateCalled;
	private:
		friend int ::main();
	};
}