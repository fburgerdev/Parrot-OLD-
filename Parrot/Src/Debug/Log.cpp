#include "Ptpch.hpp"
#include "Log.hpp"

namespace Parrot
{
	// defined in "InternalLog.cpp"
	const std::string& HIDDEN_GetLogTabs();
	uint32_t& HIDDEN_GetLineNumber();

	void Log::NewLog()
	{
		std::cout << ConsoleColor::White << '(' << HIDDEN_GetLineNumber()++ << ")\t" << HIDDEN_GetLogTabs();
	}

	void Log::IndentToCurrentLog()
	{
		std::cout << HIDDEN_GetLogTabs() << '\t';
		for (uint32_t i = 0; i < s_SpaceCount; ++i)
			std::cout << ' ';
	}

	void Log::Message(const char* format)
	{
		while (*format != '\0')
		{
			std::cout << *format;
			if (*format++ == '\n')
				IndentToCurrentLog();
		}
	}

	uint32_t Log::s_SpaceCount = 0;
}
