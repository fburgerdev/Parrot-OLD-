#include "Ptpch.hpp"
#include "StandardAssets.hpp"

namespace Parrot
{
	namespace Asset
	{
		MeshAsset quadMesh;
		MeshAsset cubeMesh;

		TexAsset whiteTex;
		ShaderAsset standardShader;

		void CreateStandardAssets()
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

			quadMesh.filepath = Utils::Filepath("Standard::QuadMesh");
			quadMesh.isQuadGeometry = true;
			quadMesh.vertices.resize(4);
			quadMesh.vertices[0] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 1.0f } };
			quadMesh.vertices[1] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 1.0f } };
			quadMesh.vertices[2] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 0.0f } };
			quadMesh.vertices[3] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 0.0f } };

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

			cubeMesh.filepath = Utils::Filepath("Standard::CubeMesh");
			cubeMesh.isQuadGeometry = true;
			cubeMesh.vertices.resize(24);
			cubeMesh.vertices[0 ] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[1 ] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[2 ] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[3 ] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, +1.0f }, { 1.0f, 0.0f } };

			cubeMesh.vertices[4 ] = { { +0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[5 ] = { { -0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[6 ] = { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[7 ] = { { +0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } };           

			cubeMesh.vertices[8 ] = { { +0.5f, +0.5f, +0.5f }, { +1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[9 ] = { { +0.5f, +0.5f, -0.5f }, { +1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[10] = { { +0.5f, -0.5f, -0.5f }, { +1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[11] = { { +0.5f, -0.5f, +0.5f }, { +1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } };

			cubeMesh.vertices[12] = { { -0.5f, +0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[13] = { { -0.5f, +0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[14] = { { -0.5f, -0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[15] = { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } };

			cubeMesh.vertices[16] = { { +0.5f, +0.5f, +0.5f }, { 0.0f, +1.0f, 0.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[17] = { { -0.5f, +0.5f, +0.5f }, { 0.0f, +1.0f, 0.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[18] = { { -0.5f, +0.5f, -0.5f }, { 0.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[19] = { { +0.5f, +0.5f, -0.5f }, { 0.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } };

			cubeMesh.vertices[20] = { { -0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } };
			cubeMesh.vertices[21] = { { +0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } };
			cubeMesh.vertices[22] = { { +0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } };
			cubeMesh.vertices[23] = { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } };

			// whiteTex
			whiteTex.filepath = Utils::Filepath("Standard::WhiteTex");
			whiteTex.size = { 1, 1 };
			whiteTex.buffer = new Math::Vec4u8[1];
			whiteTex.buffer[0] = { 255, 255, 255, 255 };

			// standardShader
			standardShader.filepath = Utils::Filepath("Standard::Shader");
			standardShader.vertexSrc =
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
				"const int lightCount = 1;\n"
				"uniform Light u_Lights[lightCount];\n"
				"vec3 CalcLighting()\n"
				"{\n"
				"	vec3 lighting = vec3(0.0f);\n"
				"	for (int i = 0; i < lightCount; i++)\n"
				"		lighting += u_Lights[i].color * max(dot(u_Lights[i].dir, -a_Normal), 0) * u_Lights[i].intensity;;\n"
				"	return lighting;\n"
				"}\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1);\n"
				"	v_TexCoords = a_TexCoords;\n"
				"	v_Lighting = CalcLighting();\n"
				"}\n";

			standardShader.fragmentSrc =
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
				"	color.rgb = v_Lighting;\n"
				"}";
		}																																		
	}
}