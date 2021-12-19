#include "Ptpch.hpp"
#include "Filestream.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	namespace Utils
	{
		FileIn::FileIn(const Utils::Filepath& filepath)
			: std::ifstream(filepath.FullPath()), m_Filepath(filepath)
		{
			if (PT_FUNC_GUARDS_ENABLED && !is_open())
				DebugOut << FileContextWarning << filepath.FullPath() << Debugstream::EndMsg;
		}
		FileIn::~FileIn()
		{
			close();
		}
		const Utils::Filepath& FileIn::GetFilepath() const
		{
			return m_Filepath;
		}

		FileOut::FileOut(const Utils::Filepath& filepath)
			: std::ofstream(filepath.FullPath()), m_Filepath(filepath)
		{
			if (PT_FUNC_GUARDS_ENABLED && !is_open())
				DebugOut << FileContextWarning << filepath.FullPath() << Debugstream::EndMsg;
		}
		FileOut::~FileOut()
		{
			close();
		}
		const Utils::Filepath& FileOut::GetFilepath() const
		{
			return m_Filepath;
		}
	}
}