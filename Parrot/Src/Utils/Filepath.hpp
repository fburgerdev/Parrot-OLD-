#pragma once
#include <string>

namespace Parrot
{
	namespace Utils
	{
		class Directory
		{
		public:
			Directory(const std::string& dir);
			Directory(const Directory& dir);
			Directory(std::string&& dir) noexcept;
			Directory(Directory&& dir) noexcept;
			Directory();

			void operator=(const std::string& dir);
			void operator=(const Directory& dir);
			void operator=(std::string&& dir) noexcept;
			void operator=(Directory&& dir) noexcept;

			std::string_view Str() const;
		private:
			std::string m_Str;

			friend std::ostream& operator<<(std::ostream& stream, const Directory& dir) { stream << dir.m_Str; return stream; }
		};
		
		class Filename
		{
		public:
			Filename(const std::string& filename);
			Filename(const Filename& filename);
			Filename(std::string&& filename) noexcept;
			Filename(Filename&& filename) noexcept;
			Filename();

			void operator=(const std::string& filename);
			void operator=(const Filename& filename);
			void operator=(std::string&& filename) noexcept;
			void operator=(Filename&& filename) noexcept;

			bool operator==(const Filename& other) const;

			std::string_view Str() const;
			std::string_view GetExt() const;
			std::string_view GetName() const;
		private:
			std::string m_Str;
			size_t m_NameLength;

			friend std::ostream& operator<<(std::ostream& stream, const Filename& filename) { stream << filename.m_Str; return stream; }
		};
		class Filepath
		{
		public:
			Filepath(const std::string& filepath);
			Filepath(const Filepath& filepath);
			Filepath(const Directory& dir, const Filename& filename);
			Filepath(std::string&& filepath) noexcept;
			Filepath(Filepath&& filepath) noexcept;
			Filepath(const Directory& dir, Filename&& filename) noexcept;
			Filepath(Directory&& dir, const Filename& filename) noexcept;
			Filepath(Directory&& dir, Filename&& filename) noexcept;
			Filepath();

			void operator=(const std::string& filepath);
			void operator=(const Filepath& filepath);
			void operator=(std::string&& filepath) noexcept;
			void operator=(Filepath&& filepath) noexcept;

			std::string FullPath() const;
			const Directory& GetDir() const;
			const Filename& GetFilename() const;
		private:
			Directory m_Dir;
			Filename m_Filename;

			friend std::ostream& operator<<(std::ostream& stream, const Filepath& filepath) { stream << filepath.m_Dir.Str() << filepath.m_Filename.Str(); return stream; }
		};
		Filepath operator+(const Directory& dir, const Filename& name);
		Filepath operator+(const Directory& dir, Filename&& name) noexcept;
		Filepath operator+(Directory&& dir, const Filename& name) noexcept;
		Filepath operator+(Directory&& dir, Filename&& name) noexcept;
	}
}

namespace std
{
	template<>
	struct hash<Parrot::Utils::Directory>
	{
		size_t operator()(const Parrot::Utils::Directory& dir) const
		{
			return hash<string>()(std::string(dir.Str()));
		}
	};
	template<>
	struct hash<Parrot::Utils::Filename>
	{
		size_t operator()(const Parrot::Utils::Filename& filename) const
		{
			return hash<string>()(std::string(filename.Str()));
		}
	};
	template<>
	struct hash<Parrot::Utils::Filepath>
	{
		size_t operator()(const Parrot::Utils::Filepath& filepath) const
		{
			return hash<string>()(std::string(filepath.FullPath()));
		}
	};
}