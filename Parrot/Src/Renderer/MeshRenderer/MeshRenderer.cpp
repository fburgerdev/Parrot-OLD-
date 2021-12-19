#include "Ptpch.hpp"
#include "MeshRenderer.hpp"
#include "Core/Application.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	Window& Internal_GetBoundWindow();
	namespace Graphics
	{
		IndexBufferAPI* CreateIndexBufferAPI(const uint32_t* indices, uint32_t count, bool isStatic = false);
		VertexBufferAPI* CreateVertexBufferAPI(const void* vertices, size_t size, bool isStatic = false);
		VertexArrayAPI* CreateVertexArrayAPI(const VertexBufferAPI* vb, const VertexBufferLayout& layout);
		TextureAPI* CreateTextureAPI(const Math::Vec4u8* buffer, Math::Vec2u size, const TextureAPI::Settings& settings);
		ShaderAPI* CreateShaderAPI(const std::string& vertexSrc, const std::string& fragmentSrc);
	}

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
		void CreateGraphicsContent(const Component::RenderObj& ro)
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
				const uint32_t ibSize = (uint32_t)ro.mesh->vertices.size() / 4;
				uint32_t* indices = new uint32_t[(size_t)ibSize * 6];
				for (uint32_t i = 0; i < ibSize; ++i)
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
			if (s_ActiveContent->shaders.find(ro.mesh->GetID()) == s_ActiveContent->shaders.end())
			{
				shader = Graphics::CreateShaderAPI(ro.shader->vertexSrc, ro.shader->fragmentSrc);
				s_ActiveContent->shaders[ro.mesh->GetID()] = shader;
			}
			else
				shader = s_ActiveContent->shaders[ro.mesh->GetID()];

			// tex
			Graphics::TextureAPI* tex;
			if (s_ActiveContent->textures.find(ro.mesh->GetID()) == s_ActiveContent->textures.end())
			{
				tex = Graphics::CreateTextureAPI(ro.tex->buffer, ro.tex->size, ro.tex->settings);
				s_ActiveContent->textures[ro.mesh->GetID()] = tex;
			}
			else
				tex = s_ActiveContent->textures[ro.mesh->GetID()];

			s_ActiveContent->meshes[ro.mesh->GetID()] = { vb, ib, va, shader, tex };
		}

		void StartCoroutine(const Component::Camera& cam)
		{
			s_ActiveContent = &s_Contents[Internal_GetBoundWindow().GetID()];
			s_Cam = &cam;
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void Push(const Component::Transform& transform, const Component::RenderObj& ro)
		{
			if (s_ActiveContent->meshes.find(ro.mesh->GetID()) == s_ActiveContent->meshes.end())
				CreateGraphicsContent(ro);
			GraphicsContent::Mesh& mesh = s_ActiveContent->meshes[ro.mesh->GetID()];
			mesh.shader->Bind();
			mesh.shader->SetUniformMat4f("u_ViewProj", s_Cam->ViewProjMat());
			mesh.shader->SetUniformMat4f("u_Transform", transform.Mat());
			mesh.tex->Bind();
			mesh.va->Bind();

			// temp
			mesh.shader->SetUniformVec3f("u_Lights[0].dir", { 0, -1, 0 });
			mesh.shader->SetUniformVec3f("u_Lights[0].color", { 0.0f, 0.0f, 1.0f });
			mesh.shader->SetUniformFloat("u_Lights[0].intensity", 1.0f);

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