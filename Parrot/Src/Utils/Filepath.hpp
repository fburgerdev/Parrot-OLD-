#pragma once
#include <string>

namespace Parrot
{
	namespace Utils
	{
		class Directory
		{
		public:
			Directory(const std::string& directory);
			Directory(const Directory& directory);
			Directory();

			void operator=(const std::string& directory);

			const std::string& String() const;
		private:
			std::string m_String;
		};
		class Filename
		{
		public:
			Filename(const std::string& filename);
			Filename(const Filename& filename);
			Filename();

			void operator=(const std::string& filename);

			const std::string& String() const;
			std::string_view GetExt() const;
			std::string_view GetName() const;
		private:
			std::string m_String;
			size_t m_NameLength;
		};
		class Filepath
		{
		public:
			Filepath(const std::string& filepath);
			Filepath(const Filepath& filepath);
			Filepath(const Directory& dir, const Filename& name);
			Filepath();

			std::string FullPath() const;
			const Directory& GetDir() const;
			const Filename& GetFilename() const;
		private:
			Directory m_Directory;
			Filename m_Filename;
		};
		Filepath operator+(const Directory& dir, const Filename& name);
	}
}