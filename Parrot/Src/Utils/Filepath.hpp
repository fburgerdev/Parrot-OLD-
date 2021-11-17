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

			const std::string& String() const;
		private:
			std::string m_String;
		};
		class Filename
		{
		public:
			Filename(const std::string& filename);
			Filename(const Filename& filename);

			const std::string& String() const;
			std::string_view GetExtension() const;
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

			std::string GetFullPath() const;
			const Directory& GetDirectory() const;
			const Filename& GetFilename() const;
		private:
			Directory m_Directory;
			Filename m_Filename;
		};
	}
}