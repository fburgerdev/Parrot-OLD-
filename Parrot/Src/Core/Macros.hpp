#pragma once

#if defined(PT_DEBUG)
	#define PT_DEBUG_CALL(X) X
	#define PT_GUARD_CALL(X) X
	#define PT_DEBUGBREAK() __debugbreak()
	#define PT_SHOW_CONSOLE
#elif defined(PT_OPTIMIZED)
	#define PT_DEBUG_CALL(X)
	#define PT_GUARD_CALL(X) X
	#define PT_DEBUGBREAK() __debugbreak()
	#define PT_SHOW_CONSOLE
#elif defined(PT_DIST)
	#define PT_DEBUG_CALL(X)
	#define PT_GUARD_CALL(X)
	#define PT_DEBUGBREAK()
	#define PT_NLOG
#else
	#error No configuration specified! Options: "PT_DEBUG", "PT_OPTIMIZED", "PT_DIST"
#endif