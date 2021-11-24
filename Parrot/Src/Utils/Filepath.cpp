#include "Ptpch.hpp"
#include "Filepath.hpp"

namespace Parrot
{
	namespace Utils
	{
		Filepath::Filepath(const std::string& filepath)
			: m_Directory(filepath.substr(0, filepath.find_last_of('\\') + 1)), m_Filename(filepath.substr(m_Directory.String().length(), filepath.length() - m_Directory.String().length())) {}
		Filepath::Filepath(const Filepath& filepath)
			: m_Directory(filepath.m_Directory), m_Filename(filepath.m_Filename) {}
		Filepath::Filepath()
			: m_Directory(), m_Filename() {}
		std::string Filepath::GetFullPath() const
		{
			return m_Directory.String() + m_Filename.String();
		}
		const Directory& Filepath::GetDirectory() const
		{
			return m_Directory;
		}
		const Filename& Filepath::GetFilename() const
		{
			return m_Filename;
		}


		Directory::Directory(const std::string& directory)
			: m_String(directory) {}
		Directory::Directory(const Directory& directory)
			: m_String(directory.m_String) {}
		Directory::Directory()
			: m_String() {}
		void Directory::operator=(const std::string& directory)
		{
			m_String = directory;
		}
		const std::string& Directory::String() const
		{
			return m_String;
		}

		Filename::Filename(const std::string& filename)
			: m_String(filename), m_NameLength(filename.find_last_of('.')) {}
		Filename::Filename(const Filename& filename)
			: m_String(filename.m_String), m_NameLength(filename.m_NameLength) {}
		Filename::Filename()
			: m_String(), m_NameLength(0) {};
		void Filename::operator=(const std::string& filename)
		{
			m_String = filename;
			m_NameLength = filename.find_last_of('.');
		}
		const std::string& Filename::String() const
		{
			return m_String;
		}
		std::string_view Filename::GetExtension() const
		{
			return std::string_view(m_String.c_str() + m_NameLength + 1, m_String.length() - m_NameLength - 1);
		}
		std::string_view Filename::GetName() const
		{
			return std::string_view(m_String.c_str(), m_NameLength);
		}
	}
}