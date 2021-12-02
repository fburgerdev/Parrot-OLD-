#pragma once
#include <unordered_map>
#include "Assets/Formats/SceneAsset.hpp"
#include "Core/Application.hpp"
#include "Core/PtObj.hpp"

int main();
class SceneObj;
namespace Parrot
{
	class Scene : public PtObj
	{
	public:
		Scene(Window& window, const Asset::SceneAsset& SceneAsset);
		~Scene();

		const std::string& GetTag() const;
		Window& GetWindow();

		void AddSceneObj(const Asset::SceneObjAsset& sceneObj);
		bool HasSceneObj(const std::string& tag);
		SceneObj& GetSceneObj(const std::string& tag);

		void RaiseEvent(Event e);
	private:
		void UpdateObjs();
		void Render();
	private:
		std::string m_Tag;
		Window& m_Window;
		std::unordered_map<std::string, uint32_t> m_SceneObjNamesakeCount;
		std::unordered_map<std::string, SceneObj*> m_SceneObjs;
		std::vector<Component::Script*> m_Scripts;
		bool m_OnCreateCalled;
	private:
		friend int ::main();
	};
}