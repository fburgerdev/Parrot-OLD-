#include "Ptpch.hpp"
#include "PtTex.hpp"
#include "Debug/InternalLog.hpp"
#include "Core/LogMessages.hpp"
#include "Core/InternalApplication.hpp"

namespace Parrot
{
	PtTex::PtTex(const Utils::Filepath& filepath)
		: PtObj(PtObjType::PtTex), m_Filepath(filepath)
	{
		std::ifstream stream(filepath.GetFullPath(), std::ios::binary);
		InternalLog::LogAssert(stream.is_open(), StreamNotOpenErrorMsg, filepath.GetFullPath());
		stream.read((char*)&m_Data.settings, sizeof(TextureAPI::Settings));
		stream.read((char*)&m_Data.size, sizeof(Math::Vec2u));
		m_Data.buffer = new uint8_t[(size_t)m_Data.size.x * (size_t)m_Data.size.y * 4];
		stream.read((char*)m_Data.buffer, (size_t)m_Data.size.x * (size_t)m_Data.size.y * 4);
		stream.close();
	}
	PtTex::~PtTex()
	{
		delete[] m_Data.buffer;
	}
	const Utils::Filepath& PtTex::GetFilepath() const
	{
		return m_Filepath;
	}

	const PtTex::Data& PtTex::GetData() const
	{
		return m_Data;
	}
}