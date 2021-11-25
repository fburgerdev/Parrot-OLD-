#pragma once
#include <unordered_map>
#include "Assets/Formats/SceneAsset.hpp"
#include "SceneObj.hpp"
#include "Core/Application.hpp"
#include "Core/PtObj.hpp"

int main();
namespace Parrot
{
	class Scene : public PtObj
	{
	public:
		Scene(Window& window, const Asset::SceneAsset& SceneAsset);
		~Scene();

		const std::string& GetTag() const;
		Window& GetWindow();

		bool HasSceneObj(const std::string& tag);
		SceneObj& GetSceneObj(const std::string& tag);

		void RaiseEvent(Event e);
	private:
		void UpdateObjs();
		void Render();
	private:
		std::string m_Tag;
		Window& m_Window;
		std::unordered_map<std::string, SceneObj*> m_SceneObjs;
		std::vector<Component::Script*> m_Scripts;
	private:
		friend int ::main();
	};
}