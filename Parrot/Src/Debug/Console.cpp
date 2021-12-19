#include "Ptpch.hpp"
#include "Console.hpp"

#include <Windows.h>
namespace Parrot
{
	static void* s_Handle;
	static Console::Color s_Color;

	void Console::Show()
	{
		ShowWindow((HWND)s_Handle, SW_SHOW);
	}
	void Console::Hide()
	{
		ShowWindow((HWND)s_Handle, SW_HIDE);
	}
	void Console::SetColor(Color color)
	{
		SetConsoleTextAttribute((HWND)s_Handle, (uint8_t)color);
	}
	
	void Console::Init(bool show)
	{
		s_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetColor(Color::White);
		if (show)
			Show();
		else
			Hide();
	}
}