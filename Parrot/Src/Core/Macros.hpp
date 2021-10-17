#pragma once

// configuration
#if defined(PT_DEBUG)
	#define PT_DEBUG_CALL(X) X
	#define PT_DEBUGBREAK() __debugbreak()
#elif defined(PT_OPTIMIZED)
	#define PT_DEBUG_CALL(X)
	#define PT_DEBUGBREAK() __debugbreak()
	#define PT_NLOG
#elif defined(PT_DIST)
	#define PT_DEBUG_CALL(X)
	#define PT_DEBUGBREAK()
	#define PT_NLOG
	#define PT_BAKE_ASSETS
#else
	#error No configuration specified! Options: "PT_DEBUG", "PT_OPTIMIZED", "PT_DIST"
#endif