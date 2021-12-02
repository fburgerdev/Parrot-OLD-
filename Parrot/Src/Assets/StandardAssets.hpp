#pragma once
#include "Assets/Formats/MeshAsset.hpp"
#include "Assets/Formats/TexAsset.hpp"
#include "Assets/Formats/ShaderAsset.hpp"

namespace Parrot
{
	namespace Asset
	{
		extern MeshAsset quadMesh;
		extern MeshAsset cubeMesh;

		extern TexAsset whiteTex;
		extern ShaderAsset standardShader;

		void CreateStandardAssets();
	}
}