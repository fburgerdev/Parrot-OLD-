#pragma once
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Shader/Shader.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include <vector>
#include <unordered_map>

struct FlatQuad
{
	Vec3i pos;
	Vec2u dim;
	Vec4f color;
	FlatQuad()
		: pos(), dim(), color() {}
	FlatQuad(Vec3u pos, Vec2u dim, Vec4f color)
		: pos(pos), dim(dim), color(color) {}
};

struct TexturedQuad
{
	Vec3i pos;
	Vec2u dim;
	uint32_t texID;
	Vec2f texPos;
	Vec2f texDim;
	Vec4f tint;
	TexturedQuad()
		: pos(), dim(), texID(0), texPos(), texDim(), tint() {}
	TexturedQuad(Vec3f pos, Vec2f dim, int32_t texSlot, Vec2f texPos, Vec2f texDim, Vec4f tint)
		: pos(pos), dim(dim), texID(texSlot), texPos(texPos), texDim(texDim), tint(tint) {}
};

class BatchRenderer2D
{
private:
	struct BatchVertex
	{
		Vec3f pos;
		Vec2f texCoords;
		Vec4f tint;
	};

	struct SubBatch
	{
		static constexpr uint32_t c_MaxQuadCount = 5000;
		BatchVertex* vertices = nullptr;
		uint32_t vertexCount = 0;
		void Init() { vertices = new BatchVertex[c_MaxQuadCount * 4]; }
		~SubBatch() { delete[] vertices; }
	};

	struct Batch
	{
		Shader shader;
		IndexBuffer ib;
		VertexBuffer vb;
		VertexArray va;
		std::unordered_map<uint32_t, SubBatch> subBatches;
		void Init();
	};

	static std::unordered_map<GLFWwindow*, Batch> s_Batches;
	static Batch* s_Batch;
public:
	static void SetContext(GLFWwindow* context);
	static void SetGlobalOffset(Vec2i offset);

	static void Flush();
	static void FlushSubBatch(uint32_t BatchID);
	static void PushQuad(const FlatQuad& quad);
	static void PushQuad(const TexturedQuad& quad);
private:
	static void PrepareFlush();
};