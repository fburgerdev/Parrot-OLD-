#include "Ptpch.hpp"
#include "Filepath.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	namespace Utils
	{
		Directory::Directory(const std::string& dir)
			: m_Str(dir) 
		{
			if (m_Str.empty() || m_Str.back() != '/')
				m_Str.push_back('/');
		}
		Directory::Directory(const Directory& dir)
			: m_Str(dir.m_Str) 
		{

		}
		Directory::Directory(std::string&& dir) noexcept
			: m_Str(std::move(dir))
		{
			if (m_Str.empty() || m_Str.back() != '/')
				m_Str.push_back('/');
		}
		Directory::Directory(Directory&& dir) noexcept
			: m_Str(std::move(dir.m_Str)) 
		{

		}
		Directory::Directory()
			: m_Str() 
		{

		}
		void Directory::operator=(const std::string& dir)
		{
			m_Str = dir;
			if (m_Str.empty() || m_Str.back() != '/')
				m_Str.push_back('/');
		}
		void Directory::operator=(const Directory& dir)
		{
			m_Str = dir.m_Str;
		}
		void Directory::operator=(std::string&& dir) noexcept
		{
			m_Str = std::move(dir);
			if (m_Str.empty() || m_Str.back() != '/')
				m_Str.push_back('/');
		}
		void Directory::operator=(Directory&& dir) noexcept
		{
			m_Str = std::move(dir.m_Str);
		}
		std::string_view Directory::Str() const
		{
			return m_Str;
		}

		Filename::Filename(const std::string& filename)
			: m_Str(filename), m_NameLength(filename.find_last_of('.'))
		{
			if (PT_FUNC_GUARDS_ENABLED && m_NameLength == filename.npos)
			{
				DebugOut << UnknownExtWarning << filename << Debugstream::EndMsg;
				m_NameLength = m_Str.length();
			}
		}
		Filename::Filename(const Filename& filename)
			: m_Str(filename.m_Str), m_NameLength(filename.m_NameLength) 
		{

		}
		Filename::Filename(std::string&& filename) noexcept
			: m_Str(std::move(filename)), m_NameLength(m_Str.find_last_of('.'))
		{
			if (PT_FUNC_GUARDS_ENABLED && m_NameLength == filename.npos)
			{
				DebugOut << UnknownExtWarning << filename << Debugstream::EndMsg;
				m_NameLength = m_Str.length();
			}
		}
		Filename::Filename(Filename&& filename) noexcept
			: m_Str(std::move(filename.m_Str)), m_NameLength(filename.m_NameLength) 
		{

		}
		Filename::Filename()
			: m_Str(), m_NameLength(0) 
		{

		}
		void Filename::operator=(const std::string& filename)
		{
			m_Str = filename;
			m_NameLength = m_Str.find_last_of('.');
			if (PT_FUNC_GUARDS_ENABLED && m_NameLength == filename.npos)
			{
				DebugOut << UnknownExtWarning << filename << Debugstream::EndMsg;
				m_NameLength = m_Str.length();
			}
		}
		void Filename::operator=(const Filename& filename)
		{
			m_Str = filename.m_Str;
			m_NameLength = filename.m_NameLength;
		}
		void Filename::operator=(std::string&& filename) noexcept
		{
			m_Str = std::move(filename);
			m_NameLength = m_Str.find_last_of('.');
			if (PT_FUNC_GUARDS_ENABLED && m_NameLength == filename.npos)
			{
				DebugOut << UnknownExtWarning << filename << Debugstream::EndMsg;
				m_NameLength = m_Str.length();
			}
		}
		void Filename::operator=(Filename&& filename) noexcept
		{
			m_Str = std::move(filename.m_Str);
			m_NameLength = filename.m_NameLength;
		}
		bool Filename::operator==(const Filename& other) const
		{
			return m_Str == other.m_Str;
		}
		std::string_view Filename::Str() const
		{
			return m_Str;
		}
		std::string_view Filename::GetExt() const
		{
			return std::string_view(m_Str.c_str() + m_NameLength + 1, m_Str.length() - m_NameLength - 1);
		}
		std::string_view Filename::GetName() const
		{
			return std::string_view(m_Str.c_str(), m_NameLength);
		}
		Filepath::Filepath(const std::string& filepath)
		{
			size_t sep = filepath.find_last_of('/');
			if (sep == filepath.npos)
			{
				m_Filename = filepath;
				return;
			}
			m_Dir = filepath.substr(0, sep + 1);
			m_Filename = filepath.substr(sep + 1, filepath.length() - sep - 1);
		}
		Filepath::Filepath(const Filepath& filepath)
			: m_Dir(filepath.m_Dir), m_Filename(filepath.m_Filename) {}
		Filepath::Filepath(const Directory& dir, const Filename& filename)
			: m_Dir(dir), m_Filename(filename) {}
		Filepath::Filepath(std::string&& filepath) noexcept
		{
			size_t sep = filepath.find_last_of('/');
			if (sep == filepath.npos)
			{
				m_Filename = std::move(filepath);
				return;
			}
			m_Dir = filepath.substr(0, sep + 1);
			m_Filename = filepath.substr(sep + 1, filepath.length() - sep - 1);
		}
		Filepath::Filepath(Filepath&& filepath) noexcept
			: m_Dir(std::move(filepath.m_Dir)), m_Filename(std::move(filepath.m_Filename)) 
		{

		}
		Filepath::Filepath(const Directory& dir, Filename&& filename) noexcept
			: m_Dir(dir), m_Filename(std::move(filename)) 
		{

		}
		Filepath::Filepath(Directory&& dir, const Filename& filename) noexcept
			: m_Dir(std::move(dir)), m_Filename(filename) 
		{

		}
		Filepath::Filepath(Directory&& dir, Filename&& filename) noexcept
			: m_Dir(std::move(dir)), m_Filename(std::move(filename)) 
		{

		}
		Filepath::Filepath()
			: m_Dir(), m_Filename() 
		{

		}
		void Filepath::operator=(const std::string& filepath)
		{
			size_t sep = filepath.find_last_of('/');
			if (sep == filepath.npos)
			{
				m_Filename = filepath;
				return;
			}
			m_Dir = filepath.substr(0, sep + 1);
			m_Filename = filepath.substr(sep + 1, filepath.length() - sep - 1);
		}
		void Filepath::operator=(const Filepath& filepath)
		{
			m_Dir = filepath.m_Dir;
			m_Filename = filepath.m_Filename;
		}
		void Filepath::operator=(std::string&& filepath) noexcept
		{
			size_t sep = filepath.find_last_of('/');
			if (sep == filepath.npos)
			{
				m_Filename = std::move(filepath);
				return;
			}
			m_Dir = filepath.substr(0, sep + 1);
			m_Filename = filepath.substr(sep + 1, filepath.length() - sep - 1);
		}
		void Filepath::operator=(Filepath&& filepath) noexcept
		{
			m_Dir = std::move(filepath.m_Dir);
			m_Filename = std::move(filepath.m_Filename);
		}
		std::string Filepath::FullPath() const
		{
			std::string cat;
			std::string_view dir = m_Dir.Str();
			std::string_view filename = m_Filename.Str();
			cat.resize(dir.length() + filename.length() + 1);
			for (size_t i = 0; i < dir.length(); ++i)
				cat[i] = dir[i];
			for (size_t i = 0; i < filename.length(); ++i)
				cat[dir.length() + i] = filename[i];
			cat[dir.length() + filename.length()] = '\0';
			return cat;
		}
		const Directory& Filepath::GetDir() const
		{
			return m_Dir;
		}
		const Filename& Filepath::GetFilename() const
		{
			return m_Filename;
		}

		Filepath operator+(const Directory& dir, const Filename& name)
		{
			return Filepath(dir, name);
		}
		Filepath operator+(const Directory& dir, Filename&& name) noexcept
		{
			return Filepath(dir, std::move(name));
		}
		Filepath operator+(Directory&& dir, const Filename& name) noexcept
		{
			return Filepath(std::move(dir), name);
		}
		Filepath operator+(Directory&& dir, Filename&& name) noexcept
		{
			return Filepath(std::move(dir), std::move(name));
		}
	}
}