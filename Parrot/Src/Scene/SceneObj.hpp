#pragma once
#include "Assets/Formats/SceneObjAsset.hpp"
#include "Components.hpp"
#include "Assets/AssetManager.hpp"

#include <unordered_map>
#include <string>

namespace Parrot
{	
	class Scene;
	class SceneObj : public PtObj
	{
	private:
		SceneObj(Scene& scene, const Asset::SceneObjAsset& asset);
	public:
		~SceneObj();

		Scene& GetScene();

		bool HasComponent(ComponentType type);

		// AddComponent
		template<class _Type, class... _Args>
		_Type& AddComponent(const _Args&... args);
		template<>
		Component::RenderObj& AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::TexAsset& texAsset, const Asset::ShaderAsset& shaderAsset);
		template<>
		Component::RenderObj& AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset, const Asset::TexAsset& texAsset);
		template<>
		Component::RenderObj& AddComponent<Component::RenderObj>(const Asset::MeshAsset& meshAsset);
		template<>
		Component::Camera& AddComponent<Component::Camera>(const float& foV, const Math::Vec2f& zRange);

		template<class _Type>
		_Type& GetComponent();

		template<class _Type>
		_Type& GetScript() { return *(_Type*)m_Scripts[typeid(_Type).hash_code()]; }
	public:
		Component::Transform transform;
	private:
		Scene& m_Scene;
		std::unordered_map<ComponentType, void*> m_Components;
		std::unordered_map<size_t, Component::Script*> m_Scripts;
	private:
		friend Scene;
	};
}