#include "Ptpch.hpp"
#include "TexAsset.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/Msgs.hpp"

namespace Parrot
{
	namespace Asset
	{
		TexAsset::TexAsset(const Utils::Filepath& filepath)
			: PtObj(PtObjType::TexAsset), m_Filepath(filepath)
		{
			std::ifstream stream(filepath.GetFullPath(), std::ios::binary);
			InternalLog::LogAssert(stream.is_open(), StreamErrorMsg, filepath.GetFullPath());
			stream.read((char*)&m_Data.settings, sizeof(Graphics::TextureAPI::Settings));
			stream.read((char*)&m_Data.size, sizeof(Math::Vec2u));
			m_Data.buffer = new uint8_t[(size_t)m_Data.size.x * (size_t)m_Data.size.y * 4];
			stream.read((char*)m_Data.buffer, (size_t)m_Data.size.x * (size_t)m_Data.size.y * 4);
			stream.close();
		}
		TexAsset::~TexAsset()
		{
			delete[] m_Data.buffer;
		}
		const Utils::Filepath& TexAsset::GetFilepath() const
		{
			return m_Filepath;
		}

		const TexAsset::Data& TexAsset::GetData() const
		{
			return m_Data;
		}
	}
}