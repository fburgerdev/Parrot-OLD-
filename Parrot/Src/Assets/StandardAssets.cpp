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
			whiteTex.size = { 1, 1 };
			whiteTex.buffer = new Math::Vec4u8[1];
			whiteTex.buffer[0] = { 255, 255, 255, 255 };

			// standardShader
			standardShader.vertexSrc =
				"#version 330 core\n"
				"layout(location = 0) in vec3 a_Position;\n"
				"layout(location = 1) in vec3 a_Normal;\n"
				"layout(location = 2) in vec2 a_TexCoords;\n"
				"\n"
				"out vec2 v_TexCoords;\n"
				"\n"
				"uniform mat4 u_Transform;\n"
				"uniform mat4 u_ViewProj;\n"
				"uniform vec3 u_CamDir;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 1);\n"
				"	v_TexCoords = a_TexCoords; //* dot(-u_CamDir, a_Normal) * dot(-u_CamDir, a_Normal) * dot(-u_CamDir, a_Normal) * 2;\n"
				"}\n";

			standardShader.fragmentSrc =
				"#version 330 core\n"           
				"layout(location = 0) out vec4 color;\n"
				"\n"
				"in vec2 v_TexCoords;\n"
				"\n"
				"uniform sampler2D u_Texture;\n"
				"uniform vec4 u_Tint;\n"
				"\n"
				"void main()\n"
				"{\n"
				"	//color = vec4(v_TexCoords, 0, 1);\n"
				"	color = texture2D(u_Texture, v_TexCoords);\n"
				"}";
		}																																		
	}
}