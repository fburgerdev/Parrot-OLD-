#include "Ptpch.hpp"
#include "Random.hpp"

namespace Parrot
{
	namespace Math
	{
		float Randf(float min, float max)
		{
			return (float)rand() / RAND_MAX * (max - min) + min;
		}
		Vec2f Rand2f()
		{
			return Normalized(Vec2f(Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f)));
		}
		Vec3f Rand3f()
		{
			return Normalized(Vec3f(Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f)));
		}
		Vec4f Rand4f()
		{
			return Normalized(Vec4f(Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f), Randf(-1.0f, 1.0f)));
		}
	}
}