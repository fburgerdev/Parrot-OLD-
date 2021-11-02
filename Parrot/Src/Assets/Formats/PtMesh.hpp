#pragma once
#include "Math/Vector.hpp"
#include "Utils/Filepath.hpp"
#include <vector>

namespace Parrot
{
	struct MeshVertex
	{
		Math::Vec3f pos;
		Math::Vec3f normal;
		Math::Vec2f texCoords;

		MeshVertex(Math::Vec3f pos, Math::Vec3f normal, Math::Vec2f texCoords)
			: pos(pos), normal(normal), texCoords(texCoords) {}
		MeshVertex()
			: pos(), normal(), texCoords() {}
	};

	class PtMesh
	{
	public:
		struct Data
		{
			uint32_t isQuadBased = 1;
			std::vector<MeshVertex> vertices;
		};
	public:
		PtMesh(const Utils::Filepath& filepath);

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}