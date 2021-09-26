#pragma once
#include <iostream>
#include <source_location>

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
	public:
		static void StartScope(const char* name);
		static void EndScope();

		template<class... Types>
		static void LogInfo(const char* format, Types... Args)
		{
			SetConsoleColor(ConsoleColor::Green);
			printf("%s[INFO] ", GetScopes());
			printf(format, Args...);
			printf("\n");
		}

		template<class... Types>
		static void LogEvent(const char* format, Types... Args)
		{
			SetConsoleColor(ConsoleColor::Blue);
			printf("%s[Event] ", GetScopes());
			printf(format, Args...);
			printf("\n");
		}

		template<class... Types>
		static void LogWarning(const char* format, Types... Args)
		{
			SetConsoleColor(ConsoleColor::Yellow);
			printf("%s[WARNING] ", GetScopes());
			printf(format, Args...);
			printf("\n");
		}

		template<class... Types>
		static void LogError(const char* format, Types... Args)
		{
			SetConsoleColor(ConsoleColor::Red);
			printf("%s[ERROR] ", GetScopes());
			printf(format, Args...);
			printf("\n");
		}
	};
}

//
//#ifndef PT_NLOG
//
//	#define PT_LOG_INIT \
//	Parrot::Log::Init();
//
//	#define PT_LOG_START_SCOPE(NAME) {                               \
//	Parrot::Log::SetConsoleColor(Parrot::Log::ConsoleColor::Purple); \
//	printf(Parrot::Log::GetScopes());                                \
//	printf("[Scope] ");									             \
//	printf(NAME);										             \
//	printf("\n");                                                    \
//	Parrot::Log::PushScope(NAME); }
//
//	#define PT_LOG_END_SCOPE \
//	Parrot::Log::PopScope();
//
//	#ifndef PT_LOG_NINFO
//		#define PT_LOG_INFO(...) {						               \
//		Parrot::Log::SetConsoleColor(Parrot::Log::ConsoleColor::Green);\
//		printf(Parrot::Log::GetScopes());                              \
//		printf("[INFO] ");									           \
//		printf(__VA_ARGS__);									       \
//		printf("\n"); }
//	#else
//		#define PT_LOG_INFO(...) {}
//	#endif
//
//	#ifndef PT_LOG_NEVENT
//		#define PT_LOG_EVENT(...) {						                   \
//			Parrot::Log::SetConsoleColor(Parrot::Log::ConsoleColor::Blue); \
//			printf(Parrot::Log::GetScopes());                              \
//			printf("[EVENT] ");									           \
//			printf(__VA_ARGS__);									       \
//			printf("\n"); }
//	#else
//		#define PT_LOG_EVENT(...) {}
//	#endif
//
//	#ifndef PT_LOG_NWARNING
//		#define PT_LOG_WARNING(...)	{					                \
//		Parrot::Log::SetConsoleColor(Parrot::Log::ConsoleColor::Yellow);\
//		printf(Parrot::Log::GetScopes());                               \
//		printf("[WARNING] ");								            \
//		printf(__VA_ARGS__);									        \
//		printf("\n"); }
//	#else
//		#define PT_LOG_WARNING(...) {}
//	#endif
//
//	#ifndef PT_LOG_NERROR
//		#define PT_LOG_ERROR(...)	{							     \
//		Parrot::Log::SetConsoleColor(Parrot::Log::ConsoleColor::Red);\
//		printf(Parrot::Log::GetScopes());                            \
//		printf("[ERROR] ");									         \
//		printf(__VA_ARGS__);									     \
//		printf("\n"); }
//	#else
//		#define PT_LOG_ERROR(...) {}
//	#endif
//#else
//	#define PT_LOG_INIT {}
//	#define PT_LOG_START_SCOPE(NAME) {}
//	#define PT_LOG_END_SCOPE {}
//	#define PT_LOG_INFO(...) {}
//	#define PT_LOG_WARNING(...) {}
//	#define PT_LOG_ERROR(...) {}
//#endif 