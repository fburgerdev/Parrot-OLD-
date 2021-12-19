#include "Ptpch.hpp"
#include "DefaultAssets.hpp"

#include "AssetManager.hpp"
#include "Core/Constructor.hpp"

namespace Parrot
{
	namespace Asset
	{
		MeshAsset* g_QuadMesh;
		MeshAsset* g_CubeMesh;

		TexAsset* g_DefaultTex;
		ShaderAsset* g_DefaultShader;

		void CreateDefaultAssets()
		{
			// coordinate system
			//                         (y)
			//                         	^
			//                         	|
			//                         	|
			//                         	0----->(x)
			//                         /
			//                        /
			//                       v
			//                     (z)
			
			// quadMesh
			//                   0-------1
			//                   |       |
			//                   |       |
			//                   |       |
			//                   3-------2

			g_QuadMesh = &Constructor::MeshAssetConstructor("Default::Quad");
			g_QuadMesh->isQuadGeometry = true;
			g_QuadMesh->vertices.resize(4);
			g_QuadMesh->vertices[0] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 1.0f } };
			g_QuadMesh->vertices[1] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 1.0f } };
			g_QuadMesh->vertices[2] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 0.0f } };
			g_QuadMesh->vertices[3] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 0.0f } };

			// cubeMesh
			//                   5:12:18-----------4:9:19
			//                     /|               /|
			//                    / |              / |
			//                   /  |             /  |
			//               0:13:17-----------1:8:16|
			//                  |6:15:23---------|-7:10:22
			//                  |  /             |  /
			//                  | /              | /
			//                  |/               |/
			//               3:14:20----------2:11:21

			g_CubeMesh = &Constructor::MeshAssetConstructor("Standard::CubeMesh");
			g_CubeMesh->isQuadGeometry = true;
			g_CubeMesh->vertices.resize(24);
			g_CubeMesh->vertices[0 ] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[1 ] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[2 ] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[3 ] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 0.0f } };

			g_CubeMesh->vertices[4 ] = { { +0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[5 ] = { { -0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[6 ] = { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[7 ] = { { +0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } };           

			g_CubeMesh->vertices[8 ] = { { +0.5f, +0.5f, +0.5f }, { +1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[9 ] = { { +0.5f, +0.5f, -0.5f }, { +1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[10] = { { +0.5f, -0.5f, -0.5f }, { +1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[11] = { { +0.5f, -0.5f, +0.5f }, { +1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } };
			
			g_CubeMesh->vertices[12] = { { -0.5f, +0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[13] = { { -0.5f, +0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[14] = { { -0.5f, -0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[15] = { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } };
			
			g_CubeMesh->vertices[16] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, +1.0f, 0.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[17] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, +1.0f, 0.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[18] = { { -0.5f, +0.5f, -0.5f }, { 0.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[19] = { { +0.5f, +0.5f, -0.5f }, { 0.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } };
			
			g_CubeMesh->vertices[20] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } };
			g_CubeMesh->vertices[21] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } };
			g_CubeMesh->vertices[22] = { { +0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } };
			g_CubeMesh->vertices[23] = { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } };

			// whiteTex
			g_DefaultTex = &Constructor::TexAssetConstructor("Default::WhiteTex");
			g_DefaultTex->size = { 1, 1 };
			g_DefaultTex->buffer = new Math::Vec4u8[1];
			g_DefaultTex->buffer[0] = { 255, 255, 255, 255 };

			// standardShader
			g_DefaultShader = &Constructor::ShaderAssetConstructor("Default::Shader");
			g_DefaultShader->vertexSrc =
				"#version 330 core\n"
				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec3 a_Normal;\n"
				"layout(location = 2) in vec2 a_TexCoords;\n"
				"\n"
				"out vec2 v_TexCoords;\n"
				"out vec3 v_Lighting;\n"
				"\n"
				"uniform mat4 u_Transform;\n"
				"uniform mat4 u_ViewProj;\n"
				"uniform vec3 u_CamDir;\n"
				"\n"
				"struct Light\n"
				"{\n"
				"	vec3 dir;\n"
				"	vec3 color;\n"
				"	float intensity;\n"
				"};\n"
				"const int maxLights = 50;\n"
				"uniform int u_LightCount = 1;\n"
				"uniform Light u_Lights[maxLights];\n"
				"vec3 CalcLighting()\n"
				"{\n"
				"	vec3 lighting = vec3(0.0f);\n"
				"	for (int i = 0; i < u_LightCount; i++)\n"
				"		lighting += u_Lights[i].color * max(dot(u_Lights[i].dir, -a_Normal), 0) * u_Lights[i].intensity;\n"
				"	return lighting;\n"
				"}\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1);\n"
				"	v_TexCoords = a_TexCoords;\n"
				"	v_Lighting = CalcLighting();\n"
				"}\n";

			g_DefaultShader->fragmentSrc =
				"#version 330 core\n"           
				"layout(location = 0) out vec4 color;\n"
				"\n"
				"in vec2 v_TexCoords;\n"
				"in vec3 v_Lighting;\n"
				"\n"
				"uniform sampler2D u_Texture;\n"
				"uniform vec4 u_Tint;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	color = texture2D(u_Texture, v_TexCoords);\n"
				"	//color.rgb = v_Lighting;\n"
				"}";
		}																																		
	}
}