#pragma once
#include "Math/Vector.hpp"

namespace Parrot
{
	namespace Graphics
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
	}
}