#include "Ptpch.hpp"
#include "Filepath.hpp"

namespace Parrot
{
	namespace Utils
	{
		void Filepath::Init(const std::string& root)
		{
			s_Root = root;
		}

		Filepath::Filepath(const std::string& filepath)
			: m_Filepath(filepath) {}

		std::string_view Filepath::Extension() const
		{
			uint32_t offset = m_Filepath.find_first_of('.') + 1;
			return std::string_view(m_Filepath.c_str() + offset, m_Filepath.size() - offset);
		}

		std::string_view Filepath::Filename() const
		{
			uint32_t offset = m_Filepath.find_last_of('/') + 1;
			return std::string_view(m_Filepath.c_str() + offset, m_Filepath.size() - offset);
		}

		std::string Filepath::s_Root;
	}
}