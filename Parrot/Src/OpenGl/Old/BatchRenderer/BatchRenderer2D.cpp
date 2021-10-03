#include "BatchRenderer2D.h"

std::unordered_map<GLFWwindow*, BatchRenderer2D::Batch> BatchRenderer2D::s_Batches;
BatchRenderer2D::Batch* BatchRenderer2D::s_Batch;

void BatchRenderer2D::Batch::Init()
{
	shader.LoadShader("Src/OpenGl/Shader/StandardShaders/Batch2D.GLSL");
	shader.Bind();
	shader.SetUniform1i("u_texture", 0);
	shader.SetUniform2f("u_offset", Vec2f(0));
	uint32_t* indices = new uint32_t[SubBatch::c_MaxQuadCount * 6];
	for (uint32_t i = 0; i < SubBatch::c_MaxQuadCount; i++)
	{
		indices[i * 6 + 0] = (i << 2) + 0;
		indices[i * 6 + 1] = (i << 2) + 1;
		indices[i * 6 + 2] = (i << 2) + 2;
		indices[i * 6 + 3] = (i << 2) + 0;
		indices[i * 6 + 4] = (i << 2) + 2;
		indices[i * 6 + 5] = (i << 2) + 3;
	}
	ib.Init(indices, SubBatch::c_MaxQuadCount * 6, true);
	vb.Init(nullptr, sizeof(BatchVertex) * SubBatch::c_MaxQuadCount * 4, false);
	VertexBufferLayout layout;
	layout.Push<float>(3); // pos
	layout.Push<float>(2); // texCoords
	layout.Push<float>(4); // tint
	va.Init(vb, layout);
}

void BatchRenderer2D::SetContext(GLFWwindow* context)
{
	if (s_Batches[context].ib.GetID() == 0)
		s_Batches[context].Init();
	s_Batch = &s_Batches[context];
}

void BatchRenderer2D::SetGlobalOffset(Vec2i offset)
{
	s_Batch->shader.Bind();
	s_Batch->shader.SetUniform2f("u_offset", (Vec2f)offset);
}

void BatchRenderer2D::Flush()
{
	PrepareFlush();
	for (auto it = s_Batch->subBatches.begin(); it != s_Batch->subBatches.end(); it++)
		if (it->second.vertices != nullptr)
			FlushSubBatch(it->first);
}

void BatchRenderer2D::FlushSubBatch(uint32_t BatchID)
{
	SubBatch& subBatch = s_Batch->subBatches[BatchID];

	s_Batch->shader.SetUniform1i("u_flatShading", (int32_t)(BatchID == 0));
	s_Batch->vb.OverwriteData(subBatch.vertices, sizeof(BatchVertex) * subBatch.vertexCount);

	if (BatchID)
		GlCall(glBindTexture(GL_TEXTURE_2D, BatchID));
	GlCall(glDrawElements(GL_TRIANGLES, (subBatch.vertexCount * 6) >> 2, GL_UNSIGNED_INT, 0));
	subBatch.vertexCount = 0;
}

void BatchRenderer2D::PrepareFlush()
{
	int32_t width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	s_Batch->shader.Bind();
	s_Batch->shader.SetUniform2f("u_windowDim", Vec2f((float)width, (float)height));
	s_Batch->vb.Bind();
	s_Batch->va.Bind();
	s_Batch->ib.Bind();

	GlCall(glActiveTexture(GL_TEXTURE0));
	GlCall(glEnable(GL_DEPTH_TEST));
	GlCall(glEnable(GL_BLEND));
	GlCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GlCall(glProvokingVertex(GL_FIRST_VERTEX_CONVENTION));
}

void BatchRenderer2D::PushQuad(const FlatQuad& quad)
{
	SubBatch& subBatch = s_Batch->subBatches[0];
	if (subBatch.vertices == nullptr)
		subBatch.Init();
	if (subBatch.vertexCount + 4 > (SubBatch::c_MaxQuadCount >>  2))
	{
		PrepareFlush();
		FlushSubBatch(0);
	}

	BatchVertex* cursor = subBatch.vertices + subBatch.vertexCount;
	cursor->pos = (Vec3f)quad.pos;
	cursor->tint = quad.color;
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f((float)quad.dim.x, 0.0f, 0.0f);
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f((Vec2f)quad.dim, 0.0f);
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f(0.0f, (float)quad.dim.y, 0.0f);
	subBatch.vertexCount += 4;
}

void BatchRenderer2D::PushQuad(const TexturedQuad& quad)
{
	SubBatch& subBatch = s_Batch->subBatches[quad.texID];
	if (subBatch.vertices == nullptr)
		subBatch.Init();
	if (subBatch.vertexCount + 4 > (SubBatch::c_MaxQuadCount >> 2))
	{
		PrepareFlush();
		FlushSubBatch(quad.texID);
	}

	BatchVertex* cursor = subBatch.vertices + subBatch.vertexCount;
	cursor->pos = (Vec3f)quad.pos;
	cursor->texCoords = quad.texPos;
	cursor->tint = quad.tint;
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f((float)quad.dim.x, 0.0f, 0.0f);
	cursor->texCoords = quad.texPos + Vec2f(quad.texDim.x, 0.0f);
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f((Vec2f)quad.dim, 0.0f);
	cursor->texCoords = quad.texPos + quad.texDim;
	cursor++;

	cursor->pos = (Vec3f)quad.pos + Vec3f(0.0f, (float)quad.dim.y, 0.0f);
	cursor->texCoords = quad.texPos + Vec2f(0.0f, quad.texDim.y);
	subBatch.vertexCount += 4;
}
