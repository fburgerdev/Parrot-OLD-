#pragma once

namespace Parrot
{
	namespace Utils
	{
		constexpr bool StrIsEqual(const char* a, const char* b)
		{
			while (*a == *b && *a != '\0')
			{
				a++; b++;
			}
			return *a == '\0' && *b == '\0';
		}
	}
}