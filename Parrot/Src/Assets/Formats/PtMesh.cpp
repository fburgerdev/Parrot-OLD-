#include "Ptpch.hpp"
#include "PtMesh.hpp"
#include "Utils/FileRead.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"
#include "Core/InternalApplication.hpp"

namespace Parrot
{
	PtMesh::PtMesh(const Utils::Filepath& filepath)
		: PtObj(PtObjType::PtMesh), m_Filepath(filepath)
	{
		std::ifstream stream(filepath.GetFullPath(), std::ios::binary);
		InternalLog::LogAssert(stream.is_open(), StreamNotOpenErrorMsg, filepath.GetFullPath());
		
		stream.read((char*)&m_Data.isQuadGeometry, 1);
		stream.read((char*)&m_Data.vertexCount, sizeof(size_t));
		m_Data.vertices = (MeshVertex*)malloc(sizeof(MeshVertex) * m_Data.vertexCount);
		stream.read((char*)m_Data.vertices, sizeof(MeshVertex) * m_Data.vertexCount);
		stream.close();
	}
	PtMesh::~PtMesh()
	{
		delete[] m_Data.vertices;
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