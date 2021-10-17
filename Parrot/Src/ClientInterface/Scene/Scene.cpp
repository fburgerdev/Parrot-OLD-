#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	// defined in "Application.cpp"
	void HIDDEN_ApplicationAddScene(const std::string& tag, Scene* scene);
	void HIDDEN_ApplicationRemoveScene(const std::string& tag);

	Scene::Scene(const std::string& tag)
		: m_Tag(tag)
	{
		HIDDEN_ApplicationAddScene(tag, this);
	}
	Scene::~Scene()
	{
		HIDDEN_ApplicationRemoveScene(m_Tag);
	}

	const std::string& Scene::GetTag() const
	{
		return m_Tag;
	}
	
	void Scene::AddSceneObject(SceneObject& sceneObject)
	{
		m_SceneObjs[sceneObject.GetTag()] = &sceneObject;
	}
	SceneObject& Scene::GetSceneObject(const std::string& tag)
	{
		InternalLog::LogAssert(m_SceneObjs.find(tag) != m_SceneObjs.end(), "SceneObject with tag \"%\" doesn't exist in Scene \"%\"!", tag, m_Tag);
		return *m_SceneObjs[tag];
	}
	void Scene::UpdateObjs()
	{

	}
	void Scene::Render()
	{ 

	}
}