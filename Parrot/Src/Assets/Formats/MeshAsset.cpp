#include "Ptpch.hpp"
#include "MeshAsset.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/Msgs.hpp"

namespace Parrot
{
	namespace Asset
	{
		MeshAsset::MeshAsset(const Utils::Filepath& filepath)
			: PtObj(PtObjType::MeshAsset), m_Filepath(filepath)
		{
			std::ifstream stream(filepath.GetFullPath(), std::ios::binary);
			InternalLog::LogAssert(stream.is_open(), StreamErrorMsg, filepath.GetFullPath());

			stream.read((char*)&m_Data.isQuadGeometry, 1);
			stream.read((char*)&m_Data.vertexCount, sizeof(size_t));
			m_Data.vertices = (Graphics::MeshVertex*)malloc(sizeof(Graphics::MeshVertex) * m_Data.vertexCount);
			stream.read((char*)m_Data.vertices, sizeof(Graphics::MeshVertex) * m_Data.vertexCount);
			stream.close();
		}
		MeshAsset::~MeshAsset()
		{
			delete[] m_Data.vertices;
		}
		const Utils::Filepath& MeshAsset::GetFilepath() const
		{
			return m_Filepath;
		}
		const MeshAsset::Data& MeshAsset::GetData() const
		{
			return m_Data;
		}
	}
}