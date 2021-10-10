#include "Ptpch.hpp"
#include "Log.hpp"

namespace Parrot
{
	std::string Log::s_NewLineTabs;
	uint8_t Log::s_NewLineSpaces;
	uint32_t Log::s_LineNumber = 0;

	bool Log::s_ShowInfo = true;
	bool Log::s_ShowEvent = true;
	bool Log::s_ShowWarning = true;
	bool Log::s_ShowError = true;

	const char* Log::s_SelectedColor = "\033[0m";
}
