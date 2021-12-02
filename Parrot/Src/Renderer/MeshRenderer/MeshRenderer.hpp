#pragma once
#include "Scene/Components.hpp"

namespace Parrot
{
	namespace MeshRenderer
	{
		void StartCoroutine(const Component::Camera& cam);
		void Push(const Component::Transform& transform, const Component::Renderobj& ro);
	}
}