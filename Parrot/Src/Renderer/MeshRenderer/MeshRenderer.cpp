#include "Ptpch.hpp"
#include "MeshRenderer.hpp"
#include "Core/Application.hpp"
#include "Assets/InternalAssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	struct GraphicsContent
	{
		struct Mesh
		{
			VertexBufferAPI* vb;
			IndexBufferAPI* ib;
			VertexArrayAPI* va;
			ShaderAPI* shader;
			TextureAPI* tex;
		};
		std::unordered_map<uint32_t, ShaderAPI*> shaders;
		std::unordered_map<uint32_t, TextureAPI*> textures;
		std::unordered_map<uint32_t, Mesh> meshes;
	};
	static std::unordered_map <uint32_t, GraphicsContent*> s_WindowGraphicsContent;
	static GraphicsContent* s_ActiveContent;
	
	static const PtShader* s_DefaultShader;
	static const Camera* s_Cam;

	namespace MeshRenderer
	{
		void CreateGraphicsContent(const Renderobj& ro)
		{
			// vb, ib, va
			VertexBufferAPI* vb = CreateVertexBufferAPI(ro.ptMesh.GetData().vertices, sizeof(MeshVertex) * ro.ptMesh.GetData().vertexCount, true);
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			VertexArrayAPI* va = CreateVertexArrayAPI(vb, layout);
			IndexBufferAPI* ib = nullptr;
			if (ro.ptMesh.GetData().isQuadGeometry)
			{
				uint32_t* indices = new uint32_t[ro.ptMesh.GetData().vertexCount * 6 / 4];
				for (uint32_t i = 0; i < (ro.ptMesh.GetData().vertexCount >> 2); ++i)
				{
					indices[i * 6 + 0] = (i << 2) + 0;	 //  0------1
					indices[i * 6 + 1] = (i << 2) + 1;	 //  | \  / |
					indices[i * 6 + 2] = (i << 2) + 2;	 //  |  \/  |
					indices[i * 6 + 3] = (i << 2) + 0;	 //  |  /\  |
					indices[i * 6 + 4] = (i << 2) + 2;	 //  | /  \ |
					indices[i * 6 + 5] = (i << 2) + 3;	 //  3------2
				}
				ib = CreateIndexBufferAPI(indices, (uint32_t)ro.ptMesh.GetData().vertexCount * 6 / 4, true);
			}
			
			// shader
			ShaderAPI* shader;
			if (s_ActiveContent->shaders.find(ro.ptMesh.GetObjID()) == s_ActiveContent->shaders.end())
			{
				shader = CreateShaderAPI(ro.ptShader.GetData().vertexSrc, ro.ptShader.GetData().fragmentSrc);
				s_ActiveContent->shaders[ro.ptMesh.GetObjID()] = shader;
			}
			else
				shader = s_ActiveContent->shaders[ro.ptMesh.GetObjID()];

			// tex
			TextureAPI* tex;
			if (s_ActiveContent->textures.find(ro.ptMesh.GetObjID()) == s_ActiveContent->textures.end())
			{
				tex = CreateTextureAPI(ro.ptTex.GetData().buffer, ro.ptTex.GetData().size, ro.ptTex.GetData().settings);
				s_ActiveContent->textures[ro.ptMesh.GetObjID()] = tex;
			}
			else
				tex = s_ActiveContent->textures[ro.ptMesh.GetObjID()];

			s_ActiveContent->meshes[ro.ptMesh.GetObjID()] = { vb, ib, va, shader, tex };
		}

		void Init()
		{
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void StartCoroutine(const Camera& cam)
		{
			s_ActiveContent = s_WindowGraphicsContent[Application::GetBoundWindow().GetObjID()];
			s_Cam = &cam;
		}

		void Push(const Transform& transform, const Renderobj& ro)
		{
			//if (s_ActiveContent->meshes.find(ro.ptMesh.GetObjID()) == s_ActiveContent->meshes.end())
			//	CreateGraphicsContent(ro);
			////ShaderAPI* shader = s_ActiveContent->shaders[ro.ptShader.GetObjID()];
			//s_DefaultShader->SetUniformMat4f("u_Transform", transform.Mat());
			//s_DefaultShader->GetShaderAPI().SetUniformMat4f("u_Transform", transform.Mat());
			//ro.ptMesh.BindMesh();
			//ro.ptTex.BindTexture();
			//if (ro.ptMesh.GetData().isQuadGeometry)
			//	glDrawElements(GL_TRIANGLES, (GLsizei)ro.ptMesh.GetData().vertexCount * 6 / 4, GL_UNSIGNED_INT, 0);
			//else
			//	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ro.ptMesh.GetData().vertexCount);

		}
	}
}