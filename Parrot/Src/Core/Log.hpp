#pragma once
#include "Ptpch.hpp"

namespace Parrot
{
	class Log
	{
	private:

		static bool s_ShowInfo;
		static bool s_ShowEvent;
		static bool s_ShowWarning;
		static bool s_ShowError;

		static std::string s_NewLineTabs;
		static uint8_t s_NewLineSpaces;

		static const char* s_SelectedColor;
		static uint32_t s_LineNumber;
	public:
		static constexpr const char* White = "\033[0m";
		static constexpr const char* Green = "\033[92m";
		static constexpr const char* Blue = "\033[96m";
		static constexpr const char* Yellow = "\033[93m";
		static constexpr const char* Red = "\033[91m";

		// Enable/Disable all logging types
		static void ToggleAll(bool state) { s_ShowInfo = state; s_ShowEvent = state; s_ShowWarning = state; s_ShowError = state; }

		// Enable/Disable info logging
		static void ToggleInfo(bool state) { s_ShowInfo = state; }
		
		// Enable/Disable event logging
		static void ToggleEvent(bool state) { s_ShowEvent = state; }
		
		// Enable/Disable warning logging
		static void ToggleWarning(bool state) { s_ShowWarning = state; }
		
		// Enable/Disable error logging
		static void ToggleError(bool state) { s_ShowError = state; }
	private:
		static void NewLog()
		{
			std::cout << White << '(' << ++s_LineNumber << ")\t" << s_NewLineTabs.c_str() << s_SelectedColor;
		}

		static void NewLine()
		{
			std::cout << s_NewLineTabs.c_str() << '\t';
			for (uint8_t i = 0; i < s_NewLineSpaces; i++)
				std::cout << ' ';
		}

		template<class Arg>
		static void PrintParameter(Arg parameter)
		{
			std::cout << parameter;
		}
		template<>
		static void PrintParameter<const char*>(const char* parameter)
		{
			while (*parameter != '\0')
			{
				std::cout << *parameter;
				if (*parameter++ == '\n')
					NewLine();
			}
		}
		template<>
		static void PrintParameter<char*>(char* parameter)
		{
			while (*parameter != '\0')
			{
				std::cout << *parameter;
				if (*parameter++ == '\n')
					NewLine();
			}
		}

		// Base Message
		static void Message(const char* format)
		{
			while (*format != '\0')
			{
				std::cout << *format;
				if (*format == '\n')
					NewLine();
				format++;
			}
		}

		// Recursive Message
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
				if (*format == '\n')
					NewLine();
				format++;
			}
		}
	public:
#ifndef PT_NLOG
		// Organizes log with scopes that indent the following logging calls
		static void StartScope(const char* name)
		{
			s_NewLineSpaces = 0;
			NewLine();
			s_SelectedColor = White;
			std::cout << s_SelectedColor << "(SCOPE) " << name << '\n';
			s_NewLineTabs.push_back('\t');
		}
		// Ends the previously started scope
		static void EndScope()
		{
			if (s_NewLineTabs.size() == 0)
				return;
			s_NewLineTabs.pop_back();
		}

		static void ContinuePreviousLog()
		{
			NewLine();
		}

		// Logs your message in green and the prefix "[INFO]" to the console
		template<class... FArgs> 
		static void LogInfo(const char* format,FArgs... fArgs)
		{
			if (!s_ShowInfo)
				return;
			NewLog();
			s_SelectedColor = Green;
			std::cout << s_SelectedColor << "[INFO] ";
			s_NewLineSpaces = 7;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		// Logs your message in blue and the prefix "[EVENT]" to the console
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs)
		{
			if (!s_ShowEvent)
				return;
			NewLog();
			s_SelectedColor = Blue;
			std::cout << s_SelectedColor << "[EVENT] ";
			s_NewLineSpaces = 8;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		// Logs your message in yellow and the prefix "[WARNING]" to the console
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs)
		{
			if (!s_ShowWarning)
				return;
			NewLog();
			s_SelectedColor = Yellow;
			std::cout << s_SelectedColor << "[WARNING] ";
			s_NewLineSpaces = 10;
			Message(format, fArgs...);
			std::cout << '\n';
		}
		// Logs your message in red and the prefix "[ERROR]" to the console
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs)
		{
			if (!s_ShowError)
				return;
			NewLog();
			s_SelectedColor = Red;
			std::cout << s_SelectedColor << "[ERROR] ";
			s_NewLineSpaces = 8;
			Message(format, fArgs...);
			std::cout << '\n';
	}
#else
		static void StartScope(const char* name) { }
		static void EndScope() { }

		static void ContinuePreviousLog() { }
		template<class... FArgs>
		static void LogInfo(const char* format, FArgs... fArgs) { }
		template<class... FArgs>
		static void LogEvent(const char* format, FArgs... fArgs) { }
		template<class... FArgs>
		static void LogWarning(const char* format, FArgs... fArgs) { }
		template<class... FArgs>
		static void LogError(const char* format, FArgs... fArgs) { }
#endif
	};
}