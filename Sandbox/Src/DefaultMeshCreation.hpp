#pragma once
#include "Ptpch.hpp"
#include "ParrotScript.hpp"

using namespace Parrot::Graphics;
static void CreateDefaultMeshes()
{
	// quad
	{
		std::ofstream stream("..//Parrot//Src//Assets//Defaults//Quad.MSH", std::ios::binary);
		MeshVertex vertices[4];
		vertices[0] = MeshVertex({ +0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f });
		vertices[1] = MeshVertex({ +0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f });
		vertices[2] = MeshVertex({ -0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f });
		vertices[3] = MeshVertex({ -0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f });
		bool quad = true;
		size_t size = 4;
		stream.write((char*)&quad, 1);
		stream.write((char*)&size, sizeof(size_t));
		stream.write((char*)vertices, sizeof(MeshVertex) * size);
		stream.close();
	}
	// cube
	{
		std::ofstream stream("..//Parrot//Src//Assets//Defaults//Cube.MSH", std::ios::binary);
		MeshVertex vertices[24];
		//vertices[0] = MeshVertex( { -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 1.0f, 1.0f });
		//vertices[1] = MeshVertex( { +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 0.0f, 1.0f });
		//vertices[2] = MeshVertex( { +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 0.0f, 0.0f });
		//vertices[3] = MeshVertex( { -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 1.0f, 0.0f });
		//						  
		//vertices[4] = MeshVertex( { +0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f });
		//vertices[5] = MeshVertex( { +0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f });
		//vertices[6] = MeshVertex( { -0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f });
		//vertices[7] = MeshVertex( { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f });
		//						  
		//vertices[8] = MeshVertex( { -0.5f, +0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f });
		//vertices[9] = MeshVertex( { -0.5f, +0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f });
		//vertices[10] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f });
		//vertices[11] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f });

		//vertices[12] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f },  { 1.0f, 0.0f });
		//vertices[13] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f },  { 1.0f, 1.0f });
		//vertices[14] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f });
		//vertices[15] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f },  { 0.0f, 0.0f });

		//vertices[16] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f });
		//vertices[17] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f });
		//vertices[18] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f });
		//vertices[19] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f });

		//vertices[20] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f },  { 1.0f, 0.0f });
		//vertices[21] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f },  { 1.0f, 1.0f });
		//vertices[22] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f },  { 0.0f, 1.0f });
		//vertices[23] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f },  { 0.0f, 0.0f });

		//    5
		//  2 1 3 0
		//    4		
		constexpr float margin = 0.00f;
		vertices[0] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 1.0f, 2.0f / 3 - margin });
		vertices[1] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 0.75f, 2.0f / 3 - margin });
		vertices[2] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 0.75f, 1.0f / 3 + margin });
		vertices[3] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { 0.0f, 0.0f, 1.0f },  { 1.0f, 1.0f / 3 + margin });

		vertices[4] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.5f, 1.0f / 3 + margin });
		vertices[5] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.5f, 2.0f / 3 - margin });
		vertices[6] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.25f, 2.0f / 3  - margin });
		vertices[7] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.25f, 1.0f / 3 + margin});

		vertices[8] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.25f, 2.0f / 3 - margin });
		vertices[9] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f,  2.0f / 3 - margin });
		vertices[10] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { -1.0f, 0.0f, 0.0f },{ 0.0f,  1.0f / 3 + margin });
		vertices[11] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f },{ 0.25f, 1.0f / 3  + margin });

		vertices[12] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.75f, 1.0f / 3 + margin });
		vertices[13] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.75f, 2.0f / 3  - margin });
		vertices[14] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.5f, 2.0f / 3 - margin });
		vertices[15] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.5f, 1.0f / 3 + margin });

		vertices[16] = MeshVertex({ -0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.25f, 0.0f + margin });
		vertices[17] = MeshVertex({ +0.5f, -0.5f, +0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.5f, 0.0f + margin });
		vertices[18] = MeshVertex({ +0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.5f, 1.0f / 3 - margin });
		vertices[19] = MeshVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.25f, 1.0f / 3- margin });

		vertices[20] = MeshVertex({ +0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, 2.0f / 3 });
		vertices[21] = MeshVertex({ +0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.5f, 1.0f });
		vertices[22] = MeshVertex({ -0.5f, +0.5f, +0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.25f, 1.0f });
		vertices[23] = MeshVertex({ -0.5f, +0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.25f, 2.0f / 3 });
		
		bool quad = true;
		size_t size = 24;
		stream.write((char*)&quad, 1);
		stream.write((char*)&size, sizeof(size_t));
		stream.write((char*)vertices, sizeof(MeshVertex) * size);
		stream.close();
	}
}