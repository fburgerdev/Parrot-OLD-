#include "Ptpch.hpp"
#include "Scene.hpp"

#include "Scene/SceneObj.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "Core/Internal_Application.hpp"
#include "Debug/Internal_Log.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const Asset::SceneAsset& sceneAsset)
		: PtObj(PtObj::Type::Scene), m_Tag(sceneAsset.filepath.GetFilename().GetName()), m_Window(window), m_OnCreateCalled(false)
	{
		for (void* obj : sceneAsset.sceneObjs)
			AddSceneObj(*(Asset::SceneObjAsset*)obj);
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
	SceneObj& Scene::AddSceneObj(const Asset::SceneObjAsset& sceneObj)
	{
		SceneObj* obj = new SceneObj(*this, sceneObj);
		if (m_SceneObjs.find(obj->m_Tag) == m_SceneObjs.end())
			m_SceneObjNamesakeCount[obj->m_Tag] = 0;
		else
		{
			uint32_t number = ++m_SceneObjNamesakeCount[obj->m_Tag];
			obj->m_Tag += '(' + std::to_string(number) + ')';
		}
		m_SceneObjs[obj->m_Tag] = obj;
		for (auto& pair : obj->m_Scripts)
			m_Scripts.push_back(pair.second);
		// instantly calls OnCreate function if obj is added after the scene creation
		if (m_OnCreateCalled)
			for (auto& pair : obj->m_Scripts)
				pair.second->OnCreate();
		return *obj;
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
		for (size_t i = 0; i < m_Scripts.size(); i++)
			m_Scripts[i]->OnEvent(e);
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
			if (pair.second->HasComponent(ComponentType::RenderObj))
			{
				MeshRenderer::Push(pair.second->transform, pair.second->GetComponent<Component::RenderObj>());
			}
		}
	}
}