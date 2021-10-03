#pragma once
#include "Window.hpp"
#include "SceneObject.hpp"

namespace Parrot
{
	namespace Renderer
	{
		void BeginScene(const SceneObject::OrthographicCamera& cam);
		void BeginScene(const SceneObject::PerspectiveCamera& cam);
		void EndScene();

		void DrawFlatQuad(const SceneObject::FlatQuad& quad);
		void DrawTexQuad(const SceneObject::TexQuad& quad);
	}
}