#pragma once
#include "Ptpch.hpp"
#include "Core/Defines.hpp"

namespace Parrot
{
	class Log
	{
	private:
		static std::string& NewLineTabs();
		static uint8_t& NewLineSpaces();
	private:
		static uint32_t s_CurrLine;
	public:
		struct ConsoleColor
		{
			static constexpr const char* White = "\033[0m";
			static constexpr const char* Green = "\033[92m";
			static constexpr const char* Blue = "\033[96m";
			static constexpr const char* Yellow = "\033[93m";
			static constexpr const char* Red = "\033[91m";
		};
	private:
		static void NewLog()
		{
			std::cout << ConsoleColor::White << '(' << s_CurrLine++ << ")\t" << NewLineTabs().c_str();
		}

		static void IndentLine()
		{
			std::cout << NewLineTabs().c_str() << '\t';
			for (uint8_t i = 0; i < NewLineSpaces(); i++)
				std::cout << ' ';
		}

		static void Message(const char* format)
		{
			while (*format != '\0')
			{
				std::cout << *format;
				if (*format == '\n')
					IndentLine();
				format++;
			}
		}
		
		template<class Arg>
		static void PrintParameter(Arg parameter)
		{
			std::cout << parameter;
		}
		template<>
		static void PrintParameter<const char*>(const char* parameter)
		{
			Message(parameter);
		}
		template<>
		static void PrintParameter<char*>(char* parameter)
		{
			Message(parameter);
		}

		template<class Arg, class... FArgs>
		static void Message(const char* format, Arg arg, FArgs... fArgs)
		{
			while (*format != '\0')
			{
				if (*format == '%')
				{
					PrintParameter(arg);
					Message(++format, fArgs...);
					return;
				}
				std::cout << *format;
				if (*format++ == '\n')
					IndentLine();
			}
		}
	public:
#ifndef PT_NLOG
		static void StartScope(const char* name)
		{
			NewLineSpaces() = 0;
			IndentLine();
			std::cout << ConsoleColor::White << "(SCOPE) " << name << '\n';
			NewLineTabs().push_back('\t');
		}
		static void EndScope()
		{
			if (NewLineTabs().size() == 0)
				return;
			NewLineTabs().pop_back();
		}
		static void EndAllScopes()
		{
			if (NewLineTabs().size() == 0)
				return;
			NewLineTabs().clear();
		}

		template<class... FArgs> 
		static void LogInfo(const char* format,FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Green << "[INFO] ";
			NewLineSpaces() = 7;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Blue << "[EVENT] ";
			NewLineSpaces() = 8;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Yellow << "[WARNING] ";
			NewLineSpaces() = 9;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs)
		{
			NewLog();
			std::cout << ConsoleColor::Red << "[ERROR] ";
			NewLineSpaces() = 8;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		template<class... FArgs>
		static void LogAssert(bool success, const char* format, FArgs... fArgs)
		{
			if (success)
				return;
			NewLog();
			static const char* s_Underlined = "\033[4m";
			static const char* s_NUnderlined = "\033[24m";
			std::cout << ConsoleColor::Red << s_Underlined << "[FATAL ERROR] ";
			NewLineSpaces() = 11;
			Message(format, fArgs...);
			std::cout << s_NUnderlined << '\n';
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
	};
}