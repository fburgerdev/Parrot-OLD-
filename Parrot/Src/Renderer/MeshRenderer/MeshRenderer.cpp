#include "Ptpch.hpp"
#include "MeshRenderer.hpp"
#include "Core/Application.hpp"
#include "Assets/Internal_AssetManager.hpp"
#include "Debug/Internal_Log.hpp"
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
		std::unordered_map<uint64_t, Graphics::ShaderAPI*> shaders;
		std::unordered_map<uint64_t, Graphics::TextureAPI*> textures;
		std::unordered_map<uint64_t, Mesh> meshes;
	};
	static std::unordered_map<uint64_t, GraphicsContent> s_Contents;
	static GraphicsContent* s_ActiveContent;
	
	//static const Asset::ShaderAsset* s_DefaultShader;
	static const Component::Camera* s_Cam;

	namespace MeshRenderer
	{
		void CreateGraphicsContent(const Component::Renderobj& ro)
		{
			// vb, ib, va
			Graphics::VertexBufferAPI* vb = CreateVertexBufferAPI(ro.mesh->vertices.data(), sizeof(Graphics::MeshVertex) * ro.mesh->vertices.size(), true);
			Graphics::VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			Graphics::VertexArrayAPI* va = Graphics::CreateVertexArrayAPI(vb, layout);
			Graphics::IndexBufferAPI* ib = nullptr;
			if (ro.mesh->isQuadGeometry)
			{
				uint32_t* indices = new uint32_t[ro.mesh->vertices.size() * 6 / 4];
				for (uint32_t i = 0; i < (ro.mesh->vertices.size() >> 2); ++i)
				{
					indices[i * 6 + 0] = (i << 2) + 0;	 //  0------1
					indices[i * 6 + 1] = (i << 2) + 1;	 //  | \  / |
					indices[i * 6 + 2] = (i << 2) + 2;	 //  |  \/  |
					indices[i * 6 + 3] = (i << 2) + 0;	 //  |  /\  |
					indices[i * 6 + 4] = (i << 2) + 2;	 //  | /  \ |
					indices[i * 6 + 5] = (i << 2) + 3;	 //  3------2
				}
				ib = Graphics::CreateIndexBufferAPI(indices, (uint32_t)ro.mesh->vertices.size() * 6 / 4, true);
			}
			
			// shader
			Graphics::ShaderAPI* shader;
			if (s_ActiveContent->shaders.find(ro.mesh->ID()) == s_ActiveContent->shaders.end())
			{
				shader = Graphics::CreateShaderAPI(ro.shader->vertexSrc, ro.shader->fragmentSrc);
				s_ActiveContent->shaders[ro.mesh->ID()] = shader;
			}
			else
				shader = s_ActiveContent->shaders[ro.mesh->ID()];

			// tex
			Graphics::TextureAPI* tex;
			if (s_ActiveContent->textures.find(ro.mesh->ID()) == s_ActiveContent->textures.end())
			{
				tex = Graphics::CreateTextureAPI(ro.tex->buffer, ro.tex->size, ro.tex->settings);
				s_ActiveContent->textures[ro.mesh->ID()] = tex;
			}
			else
				tex = s_ActiveContent->textures[ro.mesh->ID()];

			s_ActiveContent->meshes[ro.mesh->ID()] = { vb, ib, va, shader, tex };
		}

		void StartCoroutine(const Component::Camera& cam)
		{
			s_ActiveContent = &s_Contents[Application::GetBoundWindow().ID()];
			s_Cam = &cam;
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void Push(const Component::Transform& transform, const Component::Renderobj& ro)
		{
			if (s_ActiveContent->meshes.find(ro.mesh->ID()) == s_ActiveContent->meshes.end())
				CreateGraphicsContent(ro);
			GraphicsContent::Mesh& mesh = s_ActiveContent->meshes[ro.mesh->ID()];
			mesh.shader->Bind();
			mesh.shader->SetUniformMat4f("u_ViewProj", s_Cam->ViewProjMat());
			mesh.shader->SetUniformMat4f("u_Transform", transform.Mat());
			mesh.tex->Bind();
			mesh.va->Bind();
				
			if (ro.mesh->isQuadGeometry)
			{
				mesh.ib->Bind();
				glDrawElements(GL_TRIANGLES, (GLsizei)ro.mesh->vertices.size() * 6 / 4, GL_UNSIGNED_INT, 0);
			}
			else
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ro.mesh->vertices.size());

		}
	}
}