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
			Graphics::VertexBufferAPI* vb;
			Graphics::IndexBufferAPI* ib;
			Graphics::VertexArrayAPI* va;
			Graphics::ShaderAPI* shader;
			Graphics::TextureAPI* tex;
		};
		std::unordered_map<uint32_t, Graphics::ShaderAPI*> shaders;
		std::unordered_map<uint32_t, Graphics::TextureAPI*> textures;
		std::unordered_map<uint32_t, Mesh> meshes;
	};
	static std::unordered_map <uint32_t, GraphicsContent*> s_WindowGraphicsContent;
	static GraphicsContent* s_ActiveContent;
	
	static const Asset::ShaderAsset* s_DefaultShader;
	static const Component::Camera* s_Cam;

	namespace MeshRenderer
	{
		void CreateGraphicsContent(const Component::Renderobj& ro)
		{
			// vb, ib, va
			Graphics::VertexBufferAPI* vb = CreateVertexBufferAPI(ro.mesh.GetData().vertices, sizeof(Graphics::MeshVertex) * ro.mesh.GetData().vertexCount, true);
			Graphics::VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			Graphics::VertexArrayAPI* va = Graphics::CreateVertexArrayAPI(vb, layout);
			Graphics::IndexBufferAPI* ib = nullptr;
			if (ro.mesh.GetData().isQuadGeometry)
			{
				uint32_t* indices = new uint32_t[ro.mesh.GetData().vertexCount * 6 / 4];
				for (uint32_t i = 0; i < (ro.mesh.GetData().vertexCount >> 2); ++i)
				{
					indices[i * 6 + 0] = (i << 2) + 0;	 //  0------1
					indices[i * 6 + 1] = (i << 2) + 1;	 //  | \  / |
					indices[i * 6 + 2] = (i << 2) + 2;	 //  |  \/  |
					indices[i * 6 + 3] = (i << 2) + 0;	 //  |  /\  |
					indices[i * 6 + 4] = (i << 2) + 2;	 //  | /  \ |
					indices[i * 6 + 5] = (i << 2) + 3;	 //  3------2
				}
				ib = Graphics::CreateIndexBufferAPI(indices, (uint32_t)ro.mesh.GetData().vertexCount * 6 / 4, true);
			}
			
			// shader
			Graphics::ShaderAPI* shader;
			if (s_ActiveContent->shaders.find(ro.mesh.GetObjID()) == s_ActiveContent->shaders.end())
			{
				shader = Graphics::CreateShaderAPI(ro.shader.GetData().vertexSrc, ro.shader.GetData().fragmentSrc);
				s_ActiveContent->shaders[ro.mesh.GetObjID()] = shader;
			}
			else
				shader = s_ActiveContent->shaders[ro.mesh.GetObjID()];

			// tex
			Graphics::TextureAPI* tex;
			if (s_ActiveContent->textures.find(ro.mesh.GetObjID()) == s_ActiveContent->textures.end())
			{
				tex = Graphics::CreateTextureAPI(ro.tex.GetData().buffer, ro.tex.GetData().size, ro.tex.GetData().settings);
				s_ActiveContent->textures[ro.mesh.GetObjID()] = tex;
			}
			else
				tex = s_ActiveContent->textures[ro.mesh.GetObjID()];

			s_ActiveContent->meshes[ro.mesh.GetObjID()] = { vb, ib, va, shader, tex };
		}

		void Init()
		{
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void StartCoroutine(const Component::Camera& cam)
		{
			s_ActiveContent = s_WindowGraphicsContent[Application::GetBoundWindow().GetObjID()];
			s_Cam = &cam;
		}

		void Push(const Component::Transform& transform, const Component::Renderobj& ro)
		{
			//if (s_ActiveContent->meshes.find(ro.MeshAsset.GetObjID()) == s_ActiveContent->meshes.end())
			//	CreateGraphicsContent(ro);
			////ShaderAPI* shader = s_ActiveContent->shaders[ro.ShaderAsset.GetObjID()];
			//s_DefaultShader->SetUniformMat4f("u_Transform", transform.Mat());
			//s_DefaultShader->GetShaderAPI().SetUniformMat4f("u_Transform", transform.Mat());
			//ro.MeshAsset.BindMesh();
			//ro.TexAsset.BindTexture();
			//if (ro.MeshAsset.GetData().isQuadGeometry)
			//	glDrawElements(GL_TRIANGLES, (GLsizei)ro.MeshAsset.GetData().vertexCount * 6 / 4, GL_UNSIGNED_INT, 0);
			//else
			//	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ro.MeshAsset.GetData().vertexCount);

		}
	}
}