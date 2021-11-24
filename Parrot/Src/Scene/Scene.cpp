#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Scene/SceneObj.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "Core/InternalApplication.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const PtScene& ptScene)
		: PtObj(PtObjType::Scene), m_Tag(ptScene.GetFilepath().GetFilename().GetName()), m_Window(window), m_OnCreateCalled(false)
	{
		for (uint32_t i = 0; i < ptScene.GetData().objCount; ++i)
		{
			const PtSceneObj& ptObj = ptScene.GetData().objs[i];
			SceneObj* obj = new SceneObj(*this, ptObj);
			m_SceneObjs[ptObj.tag] = obj;
			for (auto& pair : obj->GetScripts())
				m_Scripts.push_back(pair.second);
		}
	}
	Scene::~Scene()
	{
		for (auto& pair : m_SceneObjs)
			delete pair.second;
	}

	const std::string& Scene::GetTag() const
	{
		return m_Tag;
	}
	Window& Scene::GetWindow()
	{
		return m_Window;
	}
	bool Scene::HasSceneObj(const std::string& tag)
	{
		return m_SceneObjs.find(tag) != m_SceneObjs.end();
	}
	SceneObj& Scene::GetSceneObj(const std::string& tag)
	{
		InternalLog::LogAssert(m_SceneObjs.find(tag) != m_SceneObjs.end(), "SceneObj with tag \"%\" doesn't exist in Scene \"%\"!", tag, m_Tag);
		return *m_SceneObjs[tag];
	}
	void Scene::RaiseEvent(Event e)
	{
		for (Script* script : m_Scripts)
			script->OnEvent(e);
	}
}