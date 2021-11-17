#pragma once
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
			static constexpr const char* Underlined = "\033[4m";
			static constexpr const char* NUnderlined = "\033[24m";
		};
		static void StartScope(const char* name);
		static void EndScope();
		static void EndAllScopes();
#ifndef PT_NLOG

		template<class... FArgs>
		static void LogInfo(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Green << "[INFO] ";
			s_SpaceCount = 7;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Blue << "[EVENT] ";
			s_SpaceCount = 8;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Yellow << "[WARNING] ";
			s_SpaceCount = 10;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Red << "[ERROR] ";
			s_SpaceCount = 8;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogAssert(bool success, const char* format, FArgs... fArgs)
		{
			if (success)
				return;
			NewLog();
			std::cout << ConsoleColor::Red << ConsoleColor::Underlined << "[FATAL ERROR] ";
			s_SpaceCount = 14;
			Message(format, fArgs...);
			std::cout << ConsoleColor::NUnderlined << std::endl;
			PT_DEBUGBREAK();
		}
#else

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
		static inline void PrintParameter(const Arg& parameter) { std::cout << parameter; }
		template<> static inline void PrintParameter<const char*>(const char* const& parameter) { Message(parameter); }
		template<> static inline void PrintParameter<std::string>(const std::string& parameter) { Message(parameter.c_str()); }

		template<class Arg, class... FArgs>
		static void Message(const char* format, const Arg& arg, const FArgs&... fArgs)
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
				{
					std::cout << ConsoleColor::NUnderlined;
					IndentToCurrentLog();
				}
			}
		}
	private:
		static uint32_t s_SpaceCount;
	};
}