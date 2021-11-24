#pragma once
#include "Scene/Components.hpp"

namespace Parrot
{
	namespace MeshRenderer
	{
		void Init();
		void StartCoroutine(const Camera& cam);
		void Push(const Transform& transform, const Renderobj& ro);
	}
}