#include "Pch.hpp"
#include "Log.hpp"

namespace Parrot
{
	static HANDLE s_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	static std::string s_NewLineTabs;

	bool Log::s_ShowInfo = true;
	bool Log::s_ShowEvent = true;
	bool Log::s_ShowWarning = true;
	bool Log::s_ShowError = true;

	void Log::SetConsoleColor(ConsoleColor color)
	{
		SetConsoleTextAttribute(s_HConsole, (uint8_t)color);
	}

	const char* Log::GetScopes()
	{
		return s_LoggingTabs.c_str();
	}

#ifndef PT_NLOG
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
#else
	void Log::StartScope(const char* name) { }
	void Log::EndScope() { }
#endif // !PT_NLOG
}
