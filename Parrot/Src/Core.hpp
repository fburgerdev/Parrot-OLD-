#pragma once
#include "Application.hpp"
#include "Log.hpp"

#ifdef PT_DEBUG
#define PT_DEBUG_CALL(X) { X }
#else
#define PT_DEBUG_CALL(X)
#endif // PT_DEBUG
namespace Parrot
{
	extern const std::string c_PathToParrot;
}