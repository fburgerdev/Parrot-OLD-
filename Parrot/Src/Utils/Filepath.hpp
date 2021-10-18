#pragma once
#include <string>

namespace Parrot
{
	namespace Utils
	{
		class Filepath
		{
		public:
			static void SetRoot(const std::string& root);

			Filepath(const std::string& filepath);

			std::string FullPath() const;
			std::string_view Extension() const;
			std::string_view Filename() const;
		private:
			static std::string s_Root;
			std::string m_Filepath;
		};
	}
}