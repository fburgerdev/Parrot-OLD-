#pragma once

namespace Parrot
{
	namespace Utils
	{
		constexpr const char* FilenameFromPath(const char* path)
		{
			const char* cursor = path;
			while (*cursor != '\0')
				cursor++;
			while (*cursor != '\\' && *cursor != '/' && cursor-- != path)
				continue;
			return ++cursor;
		}

		constexpr const char* ExtFromPath(const char* path)
		{
			const char* cursor = path;
			while (*cursor != '\0')
				cursor++;
			while (*cursor != '.' && cursor-- != path)
				continue;
			return ++cursor;
		}

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