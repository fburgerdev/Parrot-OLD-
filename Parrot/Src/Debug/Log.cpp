#include "Ptpch.hpp"
#include "Log.hpp"

namespace Parrot
{
	uint32_t Log::s_CurrLine = 1;
	
	static std::string s_NewLineTabs;
	static uint8_t s_NewLineSpaces;

	std::string& Log::NewLineTabs()
	{
		return s_NewLineTabs;
	}
	uint8_t& Log::NewLineSpaces()
	{
		return s_NewLineSpaces;
	}

	void IndentConsoleLine()
	{
		std::cout << s_NewLineTabs.c_str() << '\t';
		for (uint8_t i = 0; i < s_NewLineSpaces; i++)
			std::cout << ' ';
	}
}
