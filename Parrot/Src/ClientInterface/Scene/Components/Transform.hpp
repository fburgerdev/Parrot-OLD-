#pragma once
#include "Component.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	class Transform : public Component
	{
	private:
		// matrix
	public:
		Math::Vec3f position;
		Math::Vec3f rotation;
		Math::Vec3f scale;
	public:
		Transform()
			: position(0), rotation(0), scale(1) {}
	};
}