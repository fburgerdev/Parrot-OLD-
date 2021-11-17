#include "Ptpch.hpp"
#include "PtMesh.hpp"
#include "Utils/FileRead.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"
#include "ClientInterface/Application.hpp"

namespace Parrot
{
	PtMesh::PtMesh(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
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
		if (m_Va)
		{
			delete m_Va;
			delete m_Vb;
			if (m_Ib)
				delete m_Ib;
		}
	}

	void PtMesh::BindMesh() const
	{
		if (!m_Va)
		{
			Application::MainWindow().GetWindowAPI().Bind();
			m_Vb = CreateVertexBufferAPI(m_Data.vertices, sizeof(MeshVertex) * m_Data.vertexCount, true);
			VertexBufferLayout layout;
			layout.Push<float>(3);
			layout.Push<float>(3);
			layout.Push<float>(2);
			m_Va = CreateVertexArrayAPI(m_Vb, layout);
			if (m_Data.isQuadGeometry)
			{
				uint32_t* indices = new uint32_t[m_Data.vertexCount * 6 / 4];
				for (uint32_t i = 0; i < (m_Data.vertexCount >> 2); ++i)
				{
					indices[i * 6 + 0] = (i << 2) + 0;	 //  0------1
					indices[i * 6 + 1] = (i << 2) + 1;	 //  | \  / |
					indices[i * 6 + 2] = (i << 2) + 2;	 //  |  \/  |
					indices[i * 6 + 3] = (i << 2) + 0;	 //  |  /\  |
					indices[i * 6 + 4] = (i << 2) + 2;	 //  | /  \ |
					indices[i * 6 + 5] = (i << 2) + 3;	 //  3------2
				}
				m_Ib = CreateIndexBufferAPI(indices, (uint32_t)m_Data.vertexCount * 6 / 4, true);
			}
		}
		m_Va->Bind();
		if (m_Ib)
			m_Ib->Bind();
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