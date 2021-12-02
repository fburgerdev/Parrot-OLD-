#include "Ptpch.hpp"
#include "MeshAsset.hpp"

#include "Debug/Internal_Log.hpp"

namespace Parrot
{
	namespace Asset
	{
		MeshAsset::MeshAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::MeshAsset), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath(), std::ios::binary);
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());

			stream.read((char*)&isQuadGeometry, 1);
			size_t vertexCount;
			stream.read((char*)&vertexCount, sizeof(size_t));
			vertices.resize(vertexCount);
			stream.read((char*)vertices.data(), sizeof(Graphics::MeshVertex) * vertexCount);
			stream.close();
		}
		MeshAsset::MeshAsset()
			: PtObj(PtObj::Type::MeshAsset)
		{

		}

		void MeshAsset::SaveToFile()
		{
			std::ofstream stream(filepath.FullPath(), std::ios::binary);

			size_t vertexCount = vertices.size();
			stream.write((char*)&isQuadGeometry, 1);
			stream.write((char*)&vertexCount, sizeof(size_t));
			stream.write((char*)vertices.data(), sizeof(Graphics::MeshVertex) * vertexCount);
			stream.close();
		}
	}
}