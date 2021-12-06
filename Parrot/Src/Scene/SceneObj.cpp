#include "Ptpch.hpp"
#include "Scene.hpp"
#include "SceneObj.hpp"

#include "Debug/Internal_Log.hpp"
#include "Core/Internal_Application.hpp"

namespace Parrot
{
	SceneObj::SceneObj(Scene& scene, const Asset::SceneObjAsset& sceneObj)
		: PtObj(PtObj::Type::SceneObj), transform(sceneObj.transform), m_Tag(sceneObj.tag), m_Scene(scene)
	{
		for (auto& pair : sceneObj.components)
		{
			if (pair.first == ComponentType::RenderObj)
			{
				m_Components[ComponentType::RenderObj] = new Component::RenderObj(*(Component::RenderObj*)pair.second);
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
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::ShaderAsset& shaderAsset, const Asset::TexAsset& TexAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, shaderAsset, TexAsset);
		m_Components[ComponentType::RenderObj] = rObj;
		return *rObj;
	}
	template<>
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::ShaderAsset& shaderAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, shaderAsset, AssetManager::GetWhiteTex());
		m_Components[ComponentType::RenderObj] = rObj;
		return *rObj;
	}
	template<>
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, AssetManager::GetStandardShader(), AssetManager::GetWhiteTex());
		m_Components[ComponentType::RenderObj] = rObj;
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
	Component::RenderObj& SceneObj::GetComponent<Component::RenderObj>()
	{
		Internal_Log::LogAssert(m_Components.find(ComponentType::RenderObj) != m_Components.end(), "SceneObj \"%\" doesn't have a RenderObj component!", m_Tag);
		return *(Component::RenderObj*)m_Components[ComponentType::RenderObj];
	}
	template<>
	Component::Camera& SceneObj::GetComponent<Component::Camera>()
	{
		Internal_Log::LogAssert(m_Components.find(ComponentType::Camera) != m_Components.end(), "SceneObj \"%\" doesn't have a Camera component!", m_Tag);
		return *(Component::Camera*)m_Components[ComponentType::Camera];
	}
}
