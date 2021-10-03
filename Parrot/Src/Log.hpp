#pragma once
#include "Pch.hpp"

namespace Parrot
{
	class Log
	{
	private:
		enum class ConsoleColor : uint8_t
		{
			Green = 10, Blue = 11, Red = 12, Purple = 13, Yellow = 14, White = 15
		};

		static void SetConsoleColor(ConsoleColor color);
		static const char* GetScopes();

		static bool s_ShowInfo;
		static bool s_ShowEvent;
		static bool s_ShowWarning;
		static bool s_ShowError;
	public:
		static void StartScope(const char* name);
		static void EndScope();

		static void ToggleAll(bool state) { s_ShowInfo = state; s_ShowEvent = state; s_ShowWarning = state; s_ShowError = state; }
		static void ToggleInfo(bool state) { s_ShowInfo = state; }
		static void ToggleEvent(bool state) { s_ShowEvent = state; }
		static void ToggleWarning(bool state) { s_ShowWarning = state; }
		static void ToggleError(bool state) { s_ShowError = state; }
#ifndef PT_NLOG
#ifndef PT_LOG_NINFO
		template<typename... Types>
		static void LogInfo(const char* format, Types... args)
		{
			if (!s_ShowInfo)
				return;
			SetConsoleColor(ConsoleColor::Green);
			printf("%s[INFO] ", GetScopes());
			printf(format, args...);
			printf("\n");
		}
#else
		template<typename... Types>
		static void LogInfo(const char* format, Types... args) { }
#endif // !PT_LOG_NINFO

#ifndef PT_LOG_NEVENT
		template<typename... Types>
		static void LogEvent(const char* format, Types... args)
		{
			if (!s_ShowEvent)
				return;
			SetConsoleColor(ConsoleColor::Blue);
			printf("%s[EVENT] ", GetScopes());
			printf(format, args...);
			printf("\n");
		}
#else
		template<typename... Types>
		static void LogEvent(const char* format, Types... args) { }
#endif // !PT_LOG_NEVENT

#ifndef PT_LOG_NWARNING
		template<typename... Types>
		static void LogWarning(const char* format, Types... args)
		{
			if (!s_ShowWarning)
				return;
			SetConsoleColor(ConsoleColor::Yellow);
			printf("%s[WARNING] ", GetScopes());
			printf(format, args...);
			printf("\n");
		}
#else
		template<typename... Types>
		static void LogWarning(const char* format, Types... args) { }
#endif // !PT_LOG_NWARNING

#ifndef PT_LOG_NERROR
		template<typename... Types>
		static void LogError(const char* format, Types... args)
		{
			if (!s_ShowError)
				return;
			SetConsoleColor(ConsoleColor::Red);
			printf("%s[ERROR] ", GetScopes());
			printf(format, args...);
			printf("\n");
		}
#else
		template<typename... Types>
		static void LogError(const char* format, Types... args) { }
#endif // !PT_LOG_NERROR
#else
		template<typename... Types>
		static void LogInfo(const char* format, Types... args) { }

		template<typename... Types>
		static void LogEvent(const char* format, Types... args) { }

		template<typename... Types>
		static void LogWarning(const char* format, Types... args) { }

		template<typename... Types>
		static void LogError(const char* format, Types... args) { }
#endif // !PT_NLOG
	};
}