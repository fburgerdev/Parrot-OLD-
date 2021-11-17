#include "Ptpch.hpp"
#include "MeshRenderer.hpp"
#include "Assets/AssetManager.hpp"
#include "Debug/InternalLog.hpp"
#include <GLAD/glad.h>

namespace Parrot
{
	static PtShader* s_DefaultShader;

	namespace MeshRenderer
	{
		void Init()
		{
			s_DefaultShader = &AssetManager::GetShaderAsset("Default");
		}

		void UploadCamera(const Camera& cam)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			s_DefaultShader->GetShaderAPI().Bind();
			s_DefaultShader->GetShaderAPI().SetUniformMat4f("u_ViewProj", cam.ViewProjMat());
			s_DefaultShader->GetShaderAPI().SetUniformVec3f("u_CamDir", cam.Dir());
		}
		void Render(const Transform& transform, const Renderobject& ro)
		{
			s_DefaultShader->GetShaderAPI().SetUniformMat4f("u_Transform", transform.Mat());
			ro.ptMesh.BindMesh();
			if (ro.ptMesh.GetData().isQuadGeometry)
				glDrawElements(GL_TRIANGLES, (GLsizei)ro.ptMesh.GetData().vertexCount * 6 / 4, GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ro.ptMesh.GetData().vertexCount);

		}
	}
}