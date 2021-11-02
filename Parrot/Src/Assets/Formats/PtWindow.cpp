#include "Ptpch.hpp"
#include "PtWindow.hpp"
#include "Debug/InternalLog.hpp"

namespace Parrot
{
	PtWindow::PtWindow(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{
		std::ifstream stream(filepath.FullPath());
		InternalLog::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
		
		std::getline(stream, m_Data.defaultScene);
		stream.read((char*)&m_Data.size, sizeof(Math::Vec2u));
		stream.close();
	}

	const Utils::Filepath& PtWindow::GetFilepath() const
	{
		return m_Filepath;
	}
	const PtWindow::Data& PtWindow::GetData() const
	{
		return m_Data;
	}
}