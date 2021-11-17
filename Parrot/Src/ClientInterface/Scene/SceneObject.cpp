#include "Ptpch.hpp"
#include "SceneObject.hpp"
#include "Debug/InternalLog.hpp"
#include "ClientInterface/InternalApplication.hpp"

namespace Parrot
{
	SceneObject::SceneObject(Scene& scene, const PtSceneObject& sceneObj)
		: transform(sceneObj.transform), m_Tag(sceneObj.tag), m_Scene(scene)
	{
		for (auto& pair : sceneObj.components)
		{
			if (pair.first == ComponentType::Renderobject)
			{
				const Renderobject& ro = *(Renderobject*)pair.second;
				m_Components[ComponentType::Renderobject] = new Renderobject(ro.ptMesh, ro.ptShader);
			}
			else if (pair.first == ComponentType::Camera)
			{
				const Camera& cam = *(Camera*)pair.second;
				m_Components[ComponentType::Camera] = new Camera(transform, cam.foV, cam.zRange);
			}
		}
		for (const std::string& tag : sceneObj.scripts)
		{
			Script* script = Application::GetScript(tag)(*this);
			script->OnCreate();
			m_Scripts[tag] = script;
		}
	}
	SceneObject::~SceneObject()
	{
		for (auto& ptr : m_Components)
			delete ptr.second;
	}
	const std::string& SceneObject::GetTag() const
	{
		return m_Tag;
	}
	Scene& SceneObject::GetScene()
	{
		return m_Scene;
	}
	bool SceneObject::ContainsComponent(ComponentType type)
	{
		return m_Components.find(type) != m_Components.end();
	}

	template<>
	Renderobject& SceneObject::AddComponent<Renderobject>(const PtMesh& ptMesh, const PtShader& ptShader)
	{
		Renderobject* rObj = new Renderobject(ptMesh, ptShader);
		m_Components[ComponentType::Renderobject] = rObj;
		return *rObj;
	}
	template<>
	Camera& SceneObject::AddComponent<Camera>(const float& foV, const Math::Vec2f& zRange)
	{
		Camera* cam = new Camera(transform, foV, zRange);
		m_Components[ComponentType::Camera] = cam;
		return *cam;
	}

	template<>
	Renderobject& SceneObject::GetComponent<Renderobject>()
	{
		InternalLog::LogAssert(m_Components.find(ComponentType::Renderobject) != m_Components.end(), "SceneObject \"%\" doesn't have a Renderobject component!", m_Tag);
		return *(Renderobject*)m_Components[ComponentType::Renderobject];
	}
	template<>
	Camera& SceneObject::GetComponent<Camera>()
	{
		InternalLog::LogAssert(m_Components.find(ComponentType::Camera) != m_Components.end(), "SceneObject \"%\" doesn't have a Camera component!", m_Tag);
		return *(Camera*)m_Components[ComponentType::Camera];
	}

	std::unordered_map<std::string, Script*>& SceneObject::GetScripts()
	{
		return m_Scripts;
	}
}
