#pragma once
#include "Parrot.hpp"

using namespace Parrot;
class Quad : public SceneObject
{
public:
	Quad(const std::string& tag)
		: SceneObject(tag)
	{
		Mesh& mesh = AddComponent<Mesh>(Mesh::DefaultMesh::Quad);
	}

	~Quad()
	{

	}
};