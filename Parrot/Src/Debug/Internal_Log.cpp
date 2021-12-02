#include "Ptpch.hpp"
#include "Internal_Log.hpp"

namespace Parrot
{
	// both used by internal logging and client logging
	static std::string s_Tabs;
	static uint32_t s_lineNumber = 1;
	const std::string& HIDDEN_GetLogTabs() { return s_Tabs; }
	uint32_t& HIDDEN_GetLineNumber() { return s_lineNumber; }

#ifndef PT_NLOG
	void Internal_Log::StartScope(const char* name)
	{
		s_SpaceCount = 0;
		IndentToCurrentLog();
		std::cout << ConsoleColor::White << "[SCOPE] " << name << '\n';
		s_Tabs.push_back('\t');
	}
	void Internal_Log::EndScope()
	{
		if (s_Tabs.empty())
			return;
		s_Tabs.pop_back();
	}
	void Internal_Log::EndAllScopes()
	{
		if (s_Tabs.empty())
			return;
		s_Tabs.clear();
	}
#else
	void Internal_Log::StartScope(const char* name) {}
	void Internal_Log::EndScope() {}
	void Internal_Log::EndAllScopes() {}
#endif

	void Internal_Log::NewLog()
	{
		std::cout << ConsoleColor::White << '(' << s_lineNumber++ << ")\t" << s_Tabs;
	}

	void Internal_Log::IndentToCurrentLog()
	{
		std::cout << s_Tabs << '\t';
		for (uint32_t i = 0; i < s_SpaceCount; ++i)
			std::cout << ' ';
	}

	void Internal_Log::Message(const char* format)
	{
		while (*format != '\0')
		{
			std::cout << *format;
			if (*format++ == '\n')
				IndentToCurrentLog();
		}
	}

	uint32_t Internal_Log::s_SpaceCount = 0;
}
