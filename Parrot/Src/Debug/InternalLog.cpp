#include "Ptpch.hpp"
#include "InternalLog.hpp"

namespace Parrot
{
	// both used by internal logging and client logging
	static std::string s_Tabs;
	std::string& HIDDEN_LogTabs() { return s_Tabs; }

	void InternalLog::StartScope(const char* name)
	{
		s_SpaceCount = 0;
		IndentToCurrentLog();
		std::cout << ConsoleColor::White << "(INTERNAL SCOPE) " << name << '\n';
		s_Tabs.push_back('\t');
	}
	void InternalLog::EndScope()
	{
		if (s_Tabs.empty())
			return;
		s_Tabs.pop_back();
	}
	void InternalLog::EndAllScopes()
	{
		if (s_Tabs.empty())
			return;
		s_Tabs.clear();
	}

	void InternalLog::NewLog()
	{
		std::cout << ConsoleColor::White << '(' << s_CurrLine++ << ")\t" << s_Tabs;
	}

	void InternalLog::IndentToCurrentLog()
	{
		std::cout << s_Tabs << '\t';
		for (uint32_t i = 0; i < s_SpaceCount; i++)
			std::cout << ' ';
	}

	void InternalLog::Message(const char* format)
	{
		while (*format != '\0')
		{
			std::cout << *format;
			if (*format++ == '\n')
				IndentToCurrentLog();
		}
	}

	uint32_t InternalLog::s_CurrLine = 1;
	uint32_t InternalLog::s_SpaceCount = 0;
}
