#pragma once
#include <iostream>

constexpr const char* FilenameFromPath(const char* name)
{
	const char* cursor = name;
	while (*cursor != '\0')
		cursor++;
	while (*cursor != '\\' && *cursor != '/' && --cursor != name)
		continue;
	return ++cursor;
}

// GraphicsAPI
#if defined(PT_OPENGL)
	#define PT_GLFW
#else
	#error GraphicsAPI is undefined! Options: "PT_OPENGL"
#endif

// Mode
#if defined(PT_DEBUG)
	#define PT_DEBUG_CALL(FUNC) FUNC

	// Assert
	#define PT_ASSERT(X, MSG_FAIL) if (!(X)) { Parrot::Log::LogError("Assertion failed in file \"%\", line %: \"%\"", FilenameFromPath(__FILE__), __LINE__, MSG_FAIL); __debugbreak(); }
	#define PT_ASSERT_MSG_SUCCESS(X, MSG_FAIL, MSG_SUCCESS) if (!(X)) { Parrot::Log::LogError("Assertion failed in file \"%\", line %: \"%\"", FilenameFromPath(__FILE__), __LINE__, MSG_FAIL); __debugbreak(); } else { Parrot::Log::LogInfo(MSG_SUCCESS); }
#elif defined(PT_OPTIMIZED)
	#define PT_NLOG

	#define PT_DEBUG_CALL(FUNC)
	#define PT_ASSERT(X, MSG_FAIL)
	#define PT_ASSERT_MSG_SUCCESS(X, MSG_FAIL, MSG_SUCCESS)
#else
	#error Mode is undefined! Options: "PT_DEBUG", "PT_OPTIMIZED"
#endif