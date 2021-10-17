#pragma once
#include "Math/Vector.hpp"

namespace Parrot
{
	struct MeshVertex
	{
		Math::Vec3f pos;
		Math::Vec3f normal;
		Math::Vec2f texCoords;
	};
}