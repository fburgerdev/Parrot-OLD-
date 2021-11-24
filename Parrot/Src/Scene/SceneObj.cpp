#include "Ptpch.hpp"
#include "SceneObj.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/InternalApplication.hpp"

namespace Parrot
{
	SceneObj::SceneObj(Scene& scene, const PtSceneObj& sceneObj)
		: PtObj(PtObjType::SceneObj), transform(sceneObj.transform), m_Tag(sceneObj.tag), m_Scene(scene)
	{
		for (auto& pair : sceneObj.components)
		{
			if (pair.first == ComponentType::Renderobj)
			{
				m_Components[ComponentType::Renderobj] = new Renderobj(*(Renderobj*)pair.second);
			}
			else if (pair.first == ComponentType::Camera)
			{
				m_Components[ComponentType::Camera] = new Camera(transform, *(Camera*)pair.second);
			}
		}
		for (const std::string& tag : sceneObj.scripts)
		{
			Script* script = Application::Internal_GetScript(tag)(*this);
			m_Scripts[tag] = script;
		}
	}
	SceneObj::~SceneObj()
	{
		for (auto& ptr : m_Components)
			delete ptr.second;
	}
	const std::string& SceneObj::GetTag() const
	{
		return m_Tag;
	}
	Scene& SceneObj::GetScene()
	{
		return m_Scene;
	}
	bool SceneObj::HasComponent(ComponentType type)
	{
		return m_Components.find(type) != m_Components.end();
	}

	template<>
	Renderobj& SceneObj::AddComponent<Renderobj>(const PtMesh& ptMesh, const PtShader& ptShader, const PtTex& ptTex)
	{
		Renderobj* rObj = new Renderobj(ptMesh, ptShader, ptTex);
		m_Components[ComponentType::Renderobj] = rObj;
		return *rObj;
	}
	template<>
	Camera& SceneObj::AddComponent<Camera>(const float& foV, const Math::Vec2f& zRange)
	{
		Camera* cam = new Camera(transform, foV, zRange);
		m_Components[ComponentType::Camera] = cam;
		return *cam;
	}

	template<>
	Renderobj& SceneObj::GetComponent<Renderobj>()
	{
		InternalLog::LogAssert(m_Components.find(ComponentType::Renderobj) != m_Components.end(), "SceneObj \"%\" doesn't have a Renderobj component!", m_Tag);
		return *(Renderobj*)m_Components[ComponentType::Renderobj];
	}
	template<>
	Camera& SceneObj::GetComponent<Camera>()
	{
		InternalLog::LogAssert(m_Components.find(ComponentType::Camera) != m_Components.end(), "SceneObj \"%\" doesn't have a Camera component!", m_Tag);
		return *(Camera*)m_Components[ComponentType::Camera];
	}

	std::unordered_map<std::string, Script*>& SceneObj::GetScripts()
	{
		return m_Scripts;
	}
}
