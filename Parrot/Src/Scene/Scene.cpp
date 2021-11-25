#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Scene/SceneObj.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "Core/InternalApplication.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const Asset::SceneAsset& SceneAsset)
		: PtObj(PtObjType::Scene), m_Tag(SceneAsset.GetFilepath().GetFilename().GetName()), m_Window(window)
	{
		for (uint32_t i = 0; i < SceneAsset.GetData().objCount; ++i)
		{
			const Asset::SceneObjAsset& ptObj = SceneAsset.GetData().objs[i];
			SceneObj* obj = new SceneObj(*this, ptObj);
			m_SceneObjs[ptObj.tag] = obj;
			for (auto& pair : obj->GetScripts())
				m_Scripts.push_back(pair.second);
		}
		for (Component::Script* script : m_Scripts)
		{
			script->OnCreate();
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
		for (Component::Script* script : m_Scripts)
			script->OnEvent(e);
	}

	void Scene::UpdateObjs()
	{
		for (Component::Script* script : m_Scripts)
			script->OnUpdate();
	}
	void Scene::Render()
	{
		for (auto& pair : m_SceneObjs)
		{
			if (pair.second->HasComponent(ComponentType::Camera))
			{
				MeshRenderer::StartCoroutine(pair.second->GetComponent<Component::Camera>());
				break;
			}
		}
		for (auto& pair : m_SceneObjs)
		{
			if (pair.second->HasComponent(ComponentType::Renderobj))
			{
				MeshRenderer::Push(pair.second->transform, pair.second->GetComponent<Component::Renderobj>());
			}
		}
	}
}