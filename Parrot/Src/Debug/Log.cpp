#include "Ptpch.hpp"
#include "Log.hpp"

namespace Parrot
{
	// defined in "InternalLog.cpp"
	std::string& HIDDEN_LogTabs();

	void Log::StartScope(const char* name)
	{
		s_SpaceCount = 0;
		IndentToCurrentLog();
		std::cout << ConsoleColor::White << "(SCOPE) " << name << '\n';
		HIDDEN_LogTabs().push_back('\t');
	}
	void Log::EndScope()
	{
		if (HIDDEN_LogTabs().empty())
			return;
		HIDDEN_LogTabs().pop_back();
	}
	void Log::EndAllScopes()
	{
		if (HIDDEN_LogTabs().empty())
			return;
		HIDDEN_LogTabs().clear();
	}

	void Log::NewLog()
	{
		std::cout << ConsoleColor::White << '(' << s_CurrLine++ << ")\t" << HIDDEN_LogTabs();
	}

	void Log::IndentToCurrentLog()
	{
		std::cout << HIDDEN_LogTabs() << '\t';
		for (uint32_t i = 0; i < s_SpaceCount; i++)
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

	uint32_t Log::s_CurrLine = 1;
	uint32_t Log::s_SpaceCount = 0;
}
