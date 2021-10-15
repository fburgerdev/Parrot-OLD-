#pragma once
#include "SceneObject.hpp"

namespace Parrot
{
	class Scene
	{
	private:
		const char* m_Name;
	public:
		Scene(const char* name);

		SceneObject& CreateSceneObject(const char* name);
		void DestroySceneObject(const char* name);
		SceneObject& GetSceneObject(const char* name);
	};
}