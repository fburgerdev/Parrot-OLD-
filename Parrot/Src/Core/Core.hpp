#pragma once

#if defined(PT_DEBUG)
constexpr bool PT_FUNC_GUARDS_ENABLED = true;
constexpr bool PT_SHOW_CONSOLE = true;
#elif defined(PT_OPTIMIZED)
constexpr bool PT_FUNC_GUARDS_ENABLED = false;
constexpr bool PT_SHOW_CONSOLE = true;
#elif defined(PT_DIST)
constexpr bool PT_FUNC_GUARDS_ENABLED = false;
constexpr bool PT_SHOW_CONSOLE = false;
#else
	#error No configuration specified! Options: "PT_DEBUG", "PT_OPTIMIZED", "PT_DIST"
#endif

struct Uninitialized {}; 