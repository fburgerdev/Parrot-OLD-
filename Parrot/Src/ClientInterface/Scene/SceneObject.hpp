#pragma once
#include "Ptpch.hpp"
#include "Components/Transform.hpp"
#include "Components/Mesh.hpp"

namespace Parrot
{
	class SceneObject
	{
	public:
		Transform transform;
	public:
		SceneObject(const std::string& tag);
		virtual ~SceneObject();

		const std::string& GetTag() const;
		
		template<class _Type, class... _Args>
		_Type& AddComponent(_Args... args);
		template<>
		Mesh& AddComponent<Mesh>(Mesh::DefaultMesh defaultMesh)
		{
			Mesh* mesh = new Mesh(defaultMesh);
			m_Components[Component::Type::Mesh] = mesh;
			return *mesh;
		}
	private:
		std::string m_Tag;

		std::unordered_map<Component::Type, Component*> m_Components;
	};
}