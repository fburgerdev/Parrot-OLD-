#include "Pch.hpp"
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "GlDebug.hpp"
#include "Log.hpp"
#include "Core.hpp"
#include "Application.hpp"
#include <glad/glad.h>

namespace Parrot
{
	struct BatchID
	{
		int32_t shaderID;
		int32_t texID;

		BatchID(int32_t shaderID, int32_t texID)
			: shaderID(shaderID), texID(texID) {}

		bool operator==(const BatchID& other) const
		{
			return shaderID == other.shaderID && texID == other.texID;
		}
	};

	struct FlatVertex
	{
		Vector::Vec3f pos;
		Vector::Vec4f color;
	};

	struct TexVertex
	{
		Vector::Vec3f pos;
		Vector::Vec2f texCoords;
		Vector::Vec4f tint;
	};

	template<class Vertex>
	struct Batch
	{
	public:
		static constexpr uint32_t c_BatchCount = 1000;
		static constexpr uint32_t c_BatchSize = sizeof(Vertex) * c_BatchCount;
	public:	
		BatchID id;
		Vertex* vertices;
		uint32_t vertexCount;

		Batch()
			: id(0, 0), vertices(nullptr), vertexCount(0) {}

		void Init(BatchID batchID)
		{
			id = batchID;
			vertices = new Vertex[c_BatchCount];
		}
	};

	static IndexBuffer* s_IbQuads;

	// Flat
	static Batch<FlatVertex> s_FlatBatch;
	static Shader* s_FlatShader;
	static VertexBuffer* s_FlatVb;
	static VertexArray* s_FlatVa;

	// Textured
	static Batch<TexVertex>* s_CurrTexBatch = nullptr;
	static std::unordered_map<uint32_t, Batch<TexVertex>> s_TexBatches;
	static Shader* s_TexShader;
	static VertexBuffer* s_TexVb;
	static VertexArray* s_TexVa;

	void InitRenderer()
	{
		uint32_t* quadIndices = new uint32_t[Batch<FlatVertex>::c_BatchCount * 6 / 4];
		for (uint32_t i = 0; i < Batch<FlatVertex>::c_BatchCount / 4; i++)
		{
			quadIndices[i * 6 + 0] = i * 4 + 0;
			quadIndices[i * 6 + 1] = i * 4 + 2;
			quadIndices[i * 6 + 2] = i * 4 + 1;
			quadIndices[i * 6 + 3] = i * 4 + 0;
			quadIndices[i * 6 + 4] = i * 4 + 3;
			quadIndices[i * 6 + 5] = i * 4 + 2;
		}
		s_IbQuads = new IndexBuffer(quadIndices, Batch<FlatVertex>::c_BatchCount * 6 / 4, true);

		// Flat
		VertexBufferLayout flatLayout;
		flatLayout.Push<float>(3); // a_position
		flatLayout.Push<float>(4); // a_color
		s_FlatVb = new VertexBuffer(nullptr, Batch<FlatVertex>::c_BatchSize, false);
		s_FlatVa = new VertexArray(*s_FlatVb, flatLayout);
		s_FlatShader = new Shader(c_PathToParrot + "Src/OpenGl/Shaders/Flat.GLSL");
		s_FlatBatch.Init(BatchID(s_FlatShader->GetID(), 0));

		// Tex
		VertexBufferLayout texLayout;
		texLayout.Push<float>(3); // a_position
		texLayout.Push<float>(2); // a_texCoords
		texLayout.Push<float>(4); // a_color
		s_TexVb = new VertexBuffer(nullptr, Batch<TexVertex>::c_BatchSize, false);
		s_TexVa = new VertexArray(*s_TexVb, texLayout);
		s_TexShader = new Shader(c_PathToParrot + "Src/OpenGl/Shaders/Tex.GLSL");

		Log::LogInfo("Renderer initialized successfully!");
	}

	template<class Vertex>
	void FlushBatch(Batch<Vertex>& batch)
	{
		if (batch.vertexCount == 0)
			return;

		if (batch.id.shaderID == s_FlatShader->GetID())
		{
			s_FlatVb->Bind();
			s_FlatVb->OverwriteData(batch.vertices, sizeof(Vertex) * batch.vertexCount);
			s_FlatShader->Bind();
			s_FlatVa->Bind();
		}
		else if (batch.id.shaderID == s_TexShader->GetID())
		{
			s_TexVb->Bind();
			s_TexVb->OverwriteData(batch.vertices, sizeof(Vertex) * batch.vertexCount);
			s_TexShader->Bind();
			s_TexVa->Bind();
			GlCall(glBindTexture(GL_TEXTURE_2D, batch.id.texID));
		}
		s_IbQuads->Bind();
		GlCall(glDrawElements(GL_TRIANGLES, batch.vertexCount * 6 / 4, GL_UNSIGNED_INT, nullptr));
		batch.vertexCount = 0;
	}

	void Renderer::BeginScene(const SceneObject::OrthographicCamera& cam)
	{
		GlCall(glEnable(GL_DEPTH_TEST));
		GlCall(glEnable(GL_CULL_FACE));
		GlCall(glEnable(GL_BLEND));
		GlCall(glActiveTexture(GL_TEXTURE0));

		GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GlCall(glCullFace(GL_FRONT));
		GlCall(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION));

		// Flat
		s_FlatShader->Bind();
		s_FlatShader->SetUniform2f("u_windowDim", (Vector::Vec2f)Window::GetDim());
		s_FlatShader->SetUniform1i("u_isOrthographic", 1);
		s_FlatShader->SetUniform3f("u_camPos", cam.GetPosition());
		s_FlatShader->SetUniform2f("u_camFactor", Vector::Vec2f(2.0f) / cam.GetDim());

		// Tex
		s_TexShader->Bind();
		s_TexShader->SetUniform1i("u_Camera.cameraType", 0);
		s_TexShader->SetUniform3f("u_Camera.orthographicCamera.pos", cam.GetPosition());
		s_TexShader->SetUniform2f("u_Camera.orthographicCamera.dimFactor", Vector::Vec2f(2.0f) / cam.GetDim());
		s_TexShader->SetUniform1i("u_texture", 0);
	}

	void Renderer::BeginScene(const SceneObject::PerspectiveCamera& cam)
	{
		GlCall(glEnable(GL_DEPTH_TEST));
		GlCall(glEnable(GL_CULL_FACE));
		GlCall(glEnable(GL_BLEND));
		GlCall(glActiveTexture(GL_TEXTURE0));

		GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GlCall(glCullFace(GL_FRONT));
		GlCall(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION));

		//// Flat
		//s_FlatShader->Bind();
		//s_FlatShader->SetUniform2f("u_windowDim", (Vector::Vec2f)Window::GetDim());
		//s_FlatShader->SetUniform1i("u_isOrthographic", 0);
		//s_FlatShader->SetUniform3f("u_camPos", cam.GetPosition());
		//s_FlatShader->SetUniform2f("u_camFactor", Vector::Vec2f(2.0f) / cam.Get());
		
		// Tex
		s_TexShader->Bind();
		s_TexShader->SetUniform1i("u_Camera.cameraType", 1);
		s_TexShader->SetUniform3f("u_Camera.perspectiveCamera.pos", cam.GetPosition());
		s_TexShader->SetUniformMat4f("u_Camera.perspectiveCamera.projMat", cam.GetProjMat(), GL_TRUE);
		s_TexShader->SetUniformMat3f("u_Camera.perspectiveCamera.viewMat", cam.GetViewMat(), GL_TRUE);
		s_TexShader->SetUniform1i("u_texture", 0);
	}

	void Renderer::EndScene()
	{
		GlCall(glUseProgram(s_FlatShader->GetID()));
		FlushBatch(s_FlatBatch);
		GlCall(glUseProgram(s_TexShader->GetID()));
		for (auto& it : s_TexBatches)
			FlushBatch(it.second);
	}

	void Renderer::DrawFlatQuad(const SceneObject::FlatQuad& quad)
	{
		if (s_FlatBatch.vertexCount + 4 > s_FlatBatch.c_BatchCount)
		{
			GlCall(glUseProgram(s_FlatShader->GetID()));
			FlushBatch(s_FlatBatch);
		}
		FlatVertex* cursor = s_FlatBatch.vertices + s_FlatBatch.vertexCount;

		cursor->pos = quad.GetPosition();
		cursor->color = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(quad.GetDimension().x, 0, 0);
		cursor->color = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(quad.GetDimension(), 0);
		cursor->color = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(0, quad.GetDimension().y, 0);
		cursor->color = quad.GetColor();
		cursor++;

		s_FlatBatch.vertexCount += 4;
	}

	void Renderer::DrawTexQuad(const SceneObject::TexQuad& quad)
	{
		if (s_CurrTexBatch == nullptr || s_CurrTexBatch->id.texID != quad.GetTexture().GetID())
		{
			s_CurrTexBatch = &s_TexBatches[quad.GetTexture().GetID()];
			if (s_CurrTexBatch->vertices == nullptr)
				s_CurrTexBatch->Init(BatchID(s_TexShader->GetID(), quad.GetTexture().GetID()));
		}
		else if (s_CurrTexBatch->vertexCount + 4 > s_CurrTexBatch->c_BatchCount)
		{
			GlCall(glUseProgram(s_TexShader->GetID()));
			FlushBatch(*s_CurrTexBatch);
		}

		TexVertex* cursor = s_CurrTexBatch->vertices + s_CurrTexBatch->vertexCount;

		cursor->pos = quad.GetPosition();
		cursor->texCoords = Vector::Vec2f(0.0f);
		cursor->tint = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(quad.GetDimension().x, 0, 0);
		cursor->texCoords = Vector::Vec2f(1.0f, 0.0f);
		cursor->tint = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(quad.GetDimension(), 0);
		cursor->texCoords = Vector::Vec2f(1.0f);
		cursor->tint = quad.GetColor();
		cursor++;
		cursor->pos = quad.GetPosition() + Vector::Vec3f(0, quad.GetDimension().y, 0);
		cursor->texCoords = Vector::Vec2f(0.0f, 1.0f);
		cursor->tint = quad.GetColor();
		cursor++;

		s_CurrTexBatch->vertexCount += 4;
	}
}
