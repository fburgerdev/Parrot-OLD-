#include "Ptpch.hpp"
#include "SceneObj.hpp"
#include "Scene.hpp"
#include "Debug/Internal_Log.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	SceneObj::SceneObj(Scene& scene, const Asset::SceneObjAsset& sceneObj)
		: PtObj(PtObj::Type::SceneObj), transform(sceneObj.transform), m_Tag(sceneObj.tag), m_Scene(scene)
	{
		//if (scene.HasSceneObj(sceneObj.tag))
		//{
		//	s_WindowNamesakeCount[m_Tag] = 0;
		//}
		//else
		//	m_Tag = sceneObj.tag;
		//	uint32_t number = ++s_WindowNamesakeCount[m_Tag];
		//	m_Tag += '(' + std::to_string(number) + ')';
		//}
		for (auto& pair : sceneObj.components)
		{
			if (pair.first == ComponentType::Renderobj)
			{
				m_Components[ComponentType::Renderobj] = new Component::Renderobj(*(Component::Renderobj*)pair.second);
			}
			else if (pair.first == ComponentType::Camera)
			{
				m_Components[ComponentType::Camera] = new Component::Camera(transform, *(Component::Camera*)pair.second);
			}
		}
		for (ScriptCreationFunc func : sceneObj.scripts)
		{
			Component::Script* script = func(this);
			m_Scripts[typeid(*script).hash_code()] = script;
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
	Component::Renderobj& SceneObj::AddComponent<Component::Renderobj>(const Asset::MeshAsset& MeshAsset, const Asset::ShaderAsset& ShaderAsset, const Asset::TexAsset& TexAsset)
	{
		Component::Renderobj* rObj = new Component::Renderobj(MeshAsset, ShaderAsset, TexAsset);
		m_Components[ComponentType::Renderobj] = rObj;
		return *rObj;
	}
	template<>
	Component::Camera& SceneObj::AddComponent<Component::Camera>(const float& foV, const Math::Vec2f& zRange)
	{
		Component::Camera* cam = new Component::Camera(transform, foV, zRange);
		m_Components[ComponentType::Camera] = cam;
		return *cam;
	}

	template<>
	Component::Renderobj& SceneObj::GetComponent<Component::Renderobj>()
	{
		Internal_Log::LogAssert(m_Components.find(ComponentType::Renderobj) != m_Components.end(), "SceneObj \"%\" doesn't have a Renderobj component!", m_Tag);
		return *(Component::Renderobj*)m_Components[ComponentType::Renderobj];
	}
	template<>
	Component::Camera& SceneObj::GetComponent<Component::Camera>()
	{
		Internal_Log::LogAssert(m_Components.find(ComponentType::Camera) != m_Components.end(), "SceneObj \"%\" doesn't have a Camera component!", m_Tag);
		return *(Component::Camera*)m_Components[ComponentType::Camera];
	}
}
