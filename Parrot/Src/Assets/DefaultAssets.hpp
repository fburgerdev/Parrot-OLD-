#pragma once
#include "Assets/Formats/MeshAsset.hpp"
#include "Assets/Formats/TexAsset.hpp"
#include "Assets/Formats/ShaderAsset.hpp"

namespace Parrot
{
	namespace Asset
	{
		extern MeshAsset* g_QuadMesh;
		extern MeshAsset* g_CubeMesh;

		extern TexAsset* g_DefaultTex;
		extern ShaderAsset* g_DefaultShader;

		void CreateDefaultAssets();
	}
}