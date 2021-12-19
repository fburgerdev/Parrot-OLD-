#include "Ptpch.hpp"
#include "MeshAsset.hpp"
#include "Debug/Debugstream.hpp"
#include "Utils/Filestream.hpp"

namespace Parrot
{
	namespace Asset
	{
		MeshAsset::MeshAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName())
		{
			Utils::FileIn stream(filepath);
			if (!stream.is_open())
				return;

			stream.read((char*)&isQuadGeometry, sizeof(bool));
			size_t vertexCount;
			stream.read((char*)&vertexCount, sizeof(size_t));
			vertices.resize(vertexCount);
			stream.read((char*)vertices.data(), sizeof(Graphics::MeshVertex) * vertexCount);
		}
		MeshAsset::MeshAsset(const std::string& tag)
			: PtObj(tag) {}

		bool MeshAsset::SaveToFile(Utils::Filepath& filepath)
		{
			Utils::FileOut stream(filepath);
			if (!stream.is_open())
				return false;
			size_t vertexCount = vertices.size();
			stream.write((char*)&isQuadGeometry, sizeof(bool));
			stream.write((char*)&vertexCount, sizeof(size_t));
			stream.write((char*)vertices.data(), sizeof(Graphics::MeshVertex) * vertexCount);
			return true;
		}
	}
}