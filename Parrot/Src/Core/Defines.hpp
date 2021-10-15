#pragma once

// Configuration
#if defined(PT_DEBUG)
	#define PT_DEBUG_CALL(X) X
#elif defined(PT_OPTIMIZED)
	#define PT_NLOG
	
	#define PT_DEBUG_CALL(X)
#elif defined(PT_DIST)
	#define PT_NLOG

	#define PT_DEBUG_CALL(X)
#else
	#error No configuration specified! Options: "PT_DEBUG", "PT_OPTIMIZED", "PT_DIST"
#endif