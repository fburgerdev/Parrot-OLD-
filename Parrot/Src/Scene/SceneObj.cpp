#include "Ptpch.hpp"
#include "SceneObj.hpp"
#include "Debug/Debugstream.hpp"
#include "Scene.hpp"

namespace Parrot
{
	SceneObj::SceneObj(Scene& scene, const Asset::SceneObjAsset& asset)
		: PtObj(asset.GetTag()), transform(asset.transform), m_Scene(scene)
	{
		for (auto&[type, ptr] : asset.components)
		{
			if (type == ComponentType::RenderObj)
			{
				m_Components[ComponentType::RenderObj] = new Component::RenderObj(*(Component::RenderObj*)ptr);
			}
			else if (type == ComponentType::Camera)
			{
				m_Components[ComponentType::Camera] = new Component::Camera(transform, *(Component::Camera*)ptr);
			}
		}
		for (auto& func : asset.scripts)
		{
			Component::Script* script = func(this);
			m_Scripts[typeid(*script).hash_code()] = script;
		}
	}
	SceneObj::~SceneObj()
	{
		for (auto&[type, ptr] : m_Components)
			delete ptr;
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
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::TexAsset& texAsset, const Asset::ShaderAsset& shaderAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, texAsset, shaderAsset);
		m_Components[ComponentType::RenderObj] = rObj;
		return *rObj;
	}
	template<>
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::TexAsset& texAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, texAsset, AssetManager::GetDefaultShader());
		m_Components[ComponentType::RenderObj] = rObj;
		return *rObj;
	}
	template<>
	Component::RenderObj& SceneObj::AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset)
	{
		Component::RenderObj* rObj = new Component::RenderObj(meshAsset, AssetManager::GetDefaultTex(), AssetManager::GetDefaultShader());
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
		if (PT_FUNC_GUARDS_ENABLED && m_Components.find(ComponentType::RenderObj) == m_Components.end())
		{
			DebugOut << ComponentLookupWarning << "SceneObj \"" << m_Tag << "\" doesn't have a RenderObj component!" << Debugstream::EndMsg;
		}
		return *(Component::RenderObj*)m_Components[ComponentType::RenderObj];
	}
	template<>
	Component::Camera& SceneObj::GetComponent<Component::Camera>()
	{
		if (PT_FUNC_GUARDS_ENABLED && m_Components.find(ComponentType::Camera) == m_Components.end())
		{
			DebugOut << ComponentLookupWarning << "SceneObj \"" << m_Tag << "\" doesn't have a Camera component!" << Debugstream::EndMsg;
		}
		return *(Component::Camera*)m_Components[ComponentType::Camera];
	}
}
