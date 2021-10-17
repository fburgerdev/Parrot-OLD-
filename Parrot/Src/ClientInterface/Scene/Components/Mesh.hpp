#pragma once
#include "Ptpch.hpp"
#include "Component.hpp"

namespace Parrot
{
	class Mesh : public Component
	{
	public:
		enum class DefaultMesh : uint8_t
		{
			Quad, Cube, Sphere
		};
	public:
		DefaultMesh defaultMesh;
		Mesh(DefaultMesh defaultMesh = DefaultMesh::Quad)
			: defaultMesh(defaultMesh) {}
	};
}