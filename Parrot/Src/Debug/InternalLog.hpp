#pragma once
#include "Ptpch.hpp"
#include "Core/Macros.hpp"

namespace Parrot
{
	class InternalLog
	{
	public:
		struct ConsoleColor
		{
			static constexpr const char* White = "\033[0m";
			static constexpr const char* Green = "\033[92m";
			static constexpr const char* Blue = "\033[96m";
			static constexpr const char* Yellow = "\033[93m";
			static constexpr const char* Red = "\033[91m";
		};
#ifndef PT_NLOG
		static void StartScope(const char* name);
		static void EndScope();
		static void EndAllScopes();

		template<class... FArgs>
		static void LogInfo(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Green << "[INTERNAL INFO] ";
			s_SpaceCount = 16;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Blue << "[INTERNAL EVENT] ";
			s_SpaceCount = 17;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Yellow << "[INTERNAL WARNING] ";
			s_SpaceCount = 18;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Red << "[INTERNAL ERROR] ";
			s_SpaceCount = 17;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogAssert(bool success, const char* format, FArgs... fArgs)
		{
			static constexpr const char* s_Underlined = "\033[4m";
			static constexpr const char* s_NUnderlined = "\033[24m";
			if (success)
				return;
			NewLog();
			std::cout << ConsoleColor::Red << s_Underlined << "[FATAL ERROR] ";
			s_SpaceCount = 11;
			Message(format, fArgs...);
			std::cout << s_NUnderlined << '\n';
			PT_DEBUGBREAK();
		}
#else
		static void StartScope(const char* name) {}
		static void EndScope() {}
		static void EndAllScopes() {}

		template<class... FArgs>
		static void LogInfo(const char* format, FArgs... fArgs) {}
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs) {}
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs) {}
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs) {}
		template<class... FArgs>
		static void LogAssert(bool success, const char* format, FArgs... fArgs) {}
#endif
	private:
		static void NewLog();
		static void IndentToCurrentLog();
		static void Message(const char* format);

		template<class Arg>
		static inline void PrintParameter(Arg parameter) { std::cout << parameter; }
		template<> static inline void PrintParameter<const char*>(const char* parameter) { Message(parameter); }
		template<> static inline void PrintParameter<char*>(char* parameter) { Message(parameter); }
		template<> static inline void PrintParameter<std::string&>(std::string& parameter) { Message(parameter.c_str()); }
		template<> static inline void PrintParameter<const std::string&>(const std::string& parameter) { Message(parameter.c_str()); }


		template<class Arg, class... FArgs>
		static void Message(const char* format, Arg arg, FArgs... fArgs)
		{
			while (*format != '\0')
			{
				if (*format == '%')
				{
					PrintParameter(arg);
					return Message(++format, fArgs...);
				}
				std::cout << *format;
				if (*format++ == '\n')
					IndentToCurrentLog();
			}
		}
	private:
		static uint32_t s_CurrLine;
		static uint32_t s_SpaceCount;
	};
}