#include "Ptpch.hpp"
#include "Scene.hpp"
#include "Renderer/MeshRenderer/MeshRenderer.hpp"
#include "ClientInterface/Application.hpp"
#include "ClientInterface/Scene/SceneObject.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	Scene::Scene(Window& window, const PtScene& ptScene)
		: m_Tag(ptScene.GetFilepath().GetFilename().GetName()), m_Window(window)
	{
		for (uint32_t i = 0; i < ptScene.GetData().objCount; ++i)
		{
			const PtSceneObject& obj = ptScene.GetData().objs[i];
			m_SceneObjs[obj.tag] = new SceneObject(*this, obj);
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
	//void Scene::AddSceneObject(SceneObject& sceneObject)
	//{
	//	m_SceneObjs[sceneObject.GetTag()] = &sceneObject;
	//}
	bool Scene::ContainsSceneObject(const std::string& tag)
	{
		return m_SceneObjs.find(tag) != m_SceneObjs.end();
	}
	SceneObject& Scene::GetSceneObject(const std::string& tag)
	{
		InternalLog::LogAssert(m_SceneObjs.find(tag) != m_SceneObjs.end(), "SceneObject with tag \"%\" doesn't exist in Scene \"%\"!", tag, m_Tag);
		return *m_SceneObjs[tag];
	}
	void Scene::UpdateObjs()
	{
		for (auto& pair : m_SceneObjs)
		{
			for (auto& scriptPair : pair.second->GetScripts())
			{
				scriptPair.second->OnUpdate();
			}
		}
	}
	void Scene::HandleEvent(Event e)
	{
		for (auto& pair : m_SceneObjs)
		{
			for (auto& scriptPair : pair.second->GetScripts())
			{
				scriptPair.second->OnEvent(e);
			}
		}
	}
	void Scene::Render()
	{ 
		for (auto& pair : m_SceneObjs)
		{
			if (pair.second->ContainsComponent(ComponentType::Camera))
			{
				MeshRenderer::UploadCamera(pair.second->GetComponent<Camera>());
				break;
			}
		}
		for (auto& pair : m_SceneObjs)
			if (pair.second->ContainsComponent(ComponentType::Renderobject))
			{
				pair.second->transform.rot += Math::Vec3f(0.01f, 0.02f, 0.0f);
				pair.second->transform.pos += Math::Vec3f(0.1f) * sinf(Application::AbsTime().Seconds());
				MeshRenderer::Render(pair.second->transform, pair.second->GetComponent<Renderobject>());
			}
	}
}