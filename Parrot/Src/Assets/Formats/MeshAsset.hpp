#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Graphics/MeshVertex.hpp"

#include <vector>

namespace Parrot
{
	namespace Asset
	{
		class MeshAsset : public PtObj
		{
		public:
			MeshAsset(const Utils::Filepath& filepath);
			MeshAsset();

			void SaveToFile();
		public:
			Utils::Filepath filepath;

			bool isQuadGeometry = true;
			std::vector<Graphics::MeshVertex> vertices;
		};
	}
}