#include "Ptpch.hpp"
#include "PtMesh.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	PtMesh::PtMesh(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{
		std::ifstream stream(filepath.FullPath(), std::ios::binary);
		InternalLog::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
		stream.read((char*)&m_Data.isQuadBased, 4);
		uint32_t size;
		stream.read((char*)&size, 4);
		m_Data.vertices.reserve(size);
		stream.read((char*)&m_Data.vertices[0], sizeof(MeshVertex) * size);
		stream.close();
	}

	const Utils::Filepath& PtMesh::GetFilepath() const
	{
		return m_Filepath;
	}
	const PtMesh::Data& PtMesh::GetData() const
	{
		return m_Data;
	}
}