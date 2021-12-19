#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Debug/Debugstream.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const Asset::SceneAsset& asset)
		: PtObj(asset.GetTag()), m_Window(window), m_OnCreateCalled(false)
	{
		for (Asset::SceneObjAsset* obj : asset.sceneObjAssets)
			AddSceneObj(*obj);
	}
	Scene::~Scene()
	{
		for (auto&[tag, obj] : m_SceneObjs)
			delete obj;
	}

	Window& Scene::GetWindow()
	{
		return m_Window;
	}
	SceneObj& Scene::AddSceneObj(const Asset::SceneObjAsset& asset)
	{
		SceneObj* obj = new SceneObj(*this, asset);
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
		if (PT_FUNC_GUARDS_ENABLED && m_SceneObjs.find(tag) == m_SceneObjs.end())
		{
			DebugOut << SceneObjLookupWarning << "Scene: " << m_Tag << " Unknown SceneObj: " << tag << Debugstream::EndMsg;
		}
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
				script->OnCreate();
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