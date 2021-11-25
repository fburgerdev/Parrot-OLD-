#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Graphics/MeshVertex.hpp"

namespace Parrot
{
	namespace Asset
	{
		class MeshAsset : public PtObj
		{
		public:
			struct Data
			{
				bool isQuadGeometry = true;
				size_t vertexCount = 0;
				Graphics::MeshVertex* vertices = nullptr;
			};
		public:
			MeshAsset(const Utils::Filepath& filepath);
			~MeshAsset();

			const Utils::Filepath& GetFilepath() const;
			const Data& GetData() const;
		private:
			Utils::Filepath m_Filepath;
			Data m_Data;
		};
	}
}