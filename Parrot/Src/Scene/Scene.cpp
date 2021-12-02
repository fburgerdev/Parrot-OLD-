#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Scene/SceneObj.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "Core/Internal_Application.hpp"
#include "Debug/Internal_Log.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const Asset::SceneAsset& SceneAsset)
		: PtObj(PtObj::Type::Scene), m_Tag(SceneAsset.filepath.GetFilename().GetName()), m_Window(window), m_OnCreateCalled(false)
	{
		for (uint32_t i = 0; i < SceneAsset.objCount; ++i)
		{
			if (m_SceneObjNamesakeCount.find(m_Tag) == m_SceneObjNamesakeCount.end())
			{
				m_SceneObjNamesakeCount[m_Tag] = 0;
			}
			const Asset::SceneObjAsset& ptObj = SceneAsset.objs[i];
			SceneObj* obj = new SceneObj(*this, ptObj);
			m_SceneObjs[ptObj.tag] = obj;
			for (auto& pair : obj->m_Scripts)
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
	void Scene::AddSceneObj(const Asset::SceneObjAsset& sceneObj)
	{
	/*	if (m_SceneObjNamesakeCount.find(sceneObj.tag) == m_SceneObjNamesakeCount.end())
		{
			m_SceneObjNamesakeCount[sceneObj.tag] = 0;
			m_SceneObjs[sceneObj.tag] = new SceneObj(*this, sceneObj);
		}
		else
		{
			uint32_t number = ++m_SceneObjNamesakeCount[sceneObj.tag];
			std::string overrideTag = sceneObj.tag + '(' + std::to_string(number) + ')';
			m_SceneObjs[overrideTag] = new SceneObj(*this, overrideTag, sceneObj);
		}*/
	}
	bool Scene::HasSceneObj(const std::string& tag)
	{
		return m_SceneObjs.find(tag) != m_SceneObjs.end();
	}
	SceneObj& Scene::GetSceneObj(const std::string& tag)
	{
		Internal_Log::LogAssert(m_SceneObjs.find(tag) != m_SceneObjs.end(), "SceneObj with tag \"%\" doesn't exist in Scene \"%\"!", tag, m_Tag);
		return *m_SceneObjs[tag];
	}
	void Scene::RaiseEvent(Event e)
	{
		for (Component::Script* script : m_Scripts)
			script->OnEvent(e);
	}

	void Scene::UpdateObjs()
	{
		if (!m_OnCreateCalled)
		{
			for (Component::Script* script : m_Scripts)
			{
				script->OnCreate();
			}
			m_OnCreateCalled = true;
		}
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