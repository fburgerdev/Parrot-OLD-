#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Graphics/MeshVertex.hpp"
#include <vector>

namespace Parrot
{
	class Constructor;
	namespace Asset
	{
		class MeshAsset : public PtObj
		{
		private:
			MeshAsset(const Utils::Filepath& filepath);
			MeshAsset(const std::string& tag);
			friend Constructor;
		public:
			bool SaveToFile(Utils::Filepath& filepath);
		public:
			bool isQuadGeometry = true;
			std::vector<Graphics::MeshVertex> vertices;
		};
	}
}