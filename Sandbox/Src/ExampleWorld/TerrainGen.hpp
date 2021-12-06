#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class TerrainGen : public Component::Script
{
public:
	static constexpr size_t dim = 100;
	float maxHeight = 10.0f;
	float steepness = 0.04f;
public:
	using Script::Script;

	virtual void OnCreate() override
	{
		Asset::MeshAsset& terrain = *new Asset::MeshAsset();
		terrain.isQuadGeometry = true;
		terrain.vertices.resize(dim * dim * 4);

		Graphics::MeshVertex* raw = new Graphics::MeshVertex[(dim + 2) * (dim + 2)];
		for (size_t z = 0; z < dim + 2; z++)
			for (size_t x = 0; x < dim + 2; x++)
				raw[z * (dim + 2) + x].pos = Math::Vec3f((float)x, sinf((float)(x + z) * steepness) * maxHeight, (float)z);

		for (size_t z = 0; z < dim + 1; z++)
			for (size_t x = 0; x < dim + 1; x++)
				raw[z * (dim + 2) + x].normal = Math::Normalized(Math::CrossProduct(raw[(z + 1) * (dim + 2) + x].pos - raw[z * (dim + 2) + x].pos, raw[z * (dim + 2) + (x + 1)].pos - raw[z * (dim + 2) + x].pos));

		size_t i = 0;
		for (size_t z = 0; z < dim; z++)
		{
			for (size_t x = 0; x < dim; x++)
			{
				terrain.vertices[i++] = raw[z * (dim + 2) + x];
				terrain.vertices[i++] = raw[z * (dim + 2) + (x + 1)];
				terrain.vertices[i++] = raw[(z + 1)* (dim + 2) + (x + 1)];
				terrain.vertices[i++] = raw[(z + 1) * (dim + 2) + x];
			}
		}
		sceneObj.AddComponent<Component::RenderObj>(terrain);
	}
};

