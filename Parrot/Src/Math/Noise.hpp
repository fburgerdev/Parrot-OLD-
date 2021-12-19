#pragma once
#include "Vector.hpp"

namespace Parrot
{
	namespace Math
	{
		void InitNoise(size_t seed);
		float PerlinNoise(float offset);
		float Perlin2D(Vec2f offset);
	}
}