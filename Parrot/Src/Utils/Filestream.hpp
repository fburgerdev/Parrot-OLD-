#pragma once
#include "Filepath.hpp"

#include <fstream>

namespace Parrot
{
	namespace Utils
	{
		class FileIn : public std::ifstream
		{
		public:
			FileIn(const Utils::Filepath& filepath);
			~FileIn();

			const Utils::Filepath& GetFilepath() const;
		private:
			Utils::Filepath m_Filepath;
		};

		class FileOut : public std::ofstream
		{
		public:
			FileOut(const Utils::Filepath& filepath);
			~FileOut();

			const Utils::Filepath& GetFilepath() const;
		private:
			Utils::Filepath m_Filepath;
		};
	}
}