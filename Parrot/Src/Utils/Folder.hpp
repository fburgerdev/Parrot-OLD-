#pragma once
#include "Filepath.hpp"
#include <filesystem>

namespace Parrot
{
	namespace Utils
	{
		using recursiveIt = std::filesystem::recursive_directory_iterator;
		class Folder
		{
		public:
			Folder(const Utils::Directory& dir);
			Folder(Utils::Directory&& dir);

			class RecursiveIterator
			{
			public:
				RecursiveIterator(recursiveIt it);

				void operator++();
				bool operator!=(const RecursiveIterator& other);
				Utils::Filepath operator*();
			private:
				recursiveIt m_It;
			};
			RecursiveIterator begin() const;
			RecursiveIterator end() const;

			const Utils::Directory& GetDir() const;
		private:
			Utils::Directory m_Dir;
			bool m_ValidDir;
			recursiveIt m_RecursiveIt;
		};
	}
}