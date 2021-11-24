#pragma once
#include "Math/Vector.hpp"
#include "Utils/Filepath.hpp"
#include "Graphics/GraphicsAPI.hpp"
#include "Core/PtObj.hpp"

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

	class PtMesh : public PtObj
	{
	public:
		struct Data
		{
			bool isQuadGeometry = true;
			size_t vertexCount = 0;
			MeshVertex* vertices = nullptr;
		};
	public:
		PtMesh(const Utils::Filepath& filepath);
		~PtMesh();

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}