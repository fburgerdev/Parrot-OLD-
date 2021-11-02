#include "Ptpch.hpp"
#include "Filepath.hpp"

namespace Parrot
{
	namespace Utils
	{
		void Filepath::SetRoot(const std::string& root)
		{
			s_Root = root;
		}

		Filepath::Filepath(const std::string& filepath)
			: m_Filepath(filepath) {}

		std::string Filepath::FullPath() const
		{
			return s_Root + m_Filepath;
		}

		std::string_view Filepath::Extension() const
		{
			size_t offset = m_Filepath.find_first_of('.') + 1;
			return std::string_view(m_Filepath.c_str() + offset, m_Filepath.size() - offset);
		}
		std::string_view Filepath::Filename() const
		{
			size_t offset = m_Filepath.find_last_of('/') + 1;
			return std::string_view(m_Filepath.c_str() + offset, m_Filepath.size() - offset);
		}
		std::string_view Filepath::FilenameNExt() const
		{
			size_t start = m_Filepath.find_last_of('/') + 1;
			size_t end = m_Filepath.find_first_of('.');
			return std::string_view(m_Filepath.c_str() + start, end - start);
		}
		std::string Filepath::s_Root;
	}
}