#pragma once
#include "ClientInterface/Scene/Components.hpp"

namespace Parrot
{
	namespace MeshRenderer
	{
		void Init();
		void UploadCamera(const Camera& cam);
		void Render(const Transform& transform, const Renderobject& ro);
	}
}