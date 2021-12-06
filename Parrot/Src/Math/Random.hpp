#pragma once
#include "Vector.hpp"

namespace Parrot
{
	namespace Math
	{
		float Randf(float min = 0.0f, float max = 1.0f);
		Vec2f Rand2f();
		Vec3f Rand3f();
		Vec4f Rand4f();
	}
}