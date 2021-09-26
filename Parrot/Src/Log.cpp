#include "Log.h"
#include <Windows.h>

namespace Parrot
{
	static HANDLE s_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	static std::string s_LoggingTabs;
	
	void Log::SetConsoleColor(ConsoleColor color)
	{
		SetConsoleTextAttribute(s_HConsole, (uint8_t)color);
	}

	void Log::StartScope(const char* name)
	{
		SetConsoleColor(ConsoleColor::White);
		printf("%s[Scope]\t%s:\n", GetScopes(), name);
		s_LoggingTabs.push_back('\t');
	}

	void Log::EndScope()
	{
		if (s_LoggingTabs.empty())
		{
			LogWarning("No scopes exist!");
			return;
		}
		s_LoggingTabs.pop_back();
	}

	const char* Log::GetScopes()
	{
		return s_LoggingTabs.c_str();
	}
}
