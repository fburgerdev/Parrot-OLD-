#pragma once
#include <unordered_map>
#include "Assets/Formats/PtScene.hpp"
#include "SceneObj.hpp"
#include "Core/Application.hpp"
#include "Core/PtObj.hpp"

int main();
namespace Parrot
{
	class Scene : public PtObj
	{
	public:
		Scene(Window& window, const PtScene& ptScene);
		~Scene();

		const std::string& GetTag() const;
		Window& GetWindow();

		bool HasSceneObj(const std::string& tag);
		SceneObj& GetSceneObj(const std::string& tag);

		void RaiseEvent(Event e);
	private:
		std::string m_Tag;
		Window& m_Window;
		std::unordered_map<std::string, SceneObj*> m_SceneObjs;
		std::vector<Script*> m_Scripts;
		bool m_OnCreateCalled;
	private:
		friend int ::main();
	};
}