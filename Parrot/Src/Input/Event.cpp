#include "Ptpch.hpp"
#include "Core/Log.hpp"
#include "Event.hpp"

namespace Parrot
{
	namespace Input
	{
		static constexpr const char* s_MouseButtonStrings[3] = { "Left", "Right", "Middle" };
		static constexpr const char* s_MouseButtonActionStrings[2] = { "Release", "Press" };
		static constexpr const char* s_KeyboardActionString[3] = { "Release", "Press", "Repeat" };
		static const char* s_KeyStrings[350];
		void Parrot::Input::Event::Log() const
		{
			switch (type)
			{
			case Type::WindowResizeEvent:
				Log::LogEvent("WindowResizeEvent: dim = %", windowResizeEvent.dim);
				break;
			case Type::WindowMaximizeEvent:
				Log::LogEvent("WindowMaximizeEvent:");
				break;
			case Type::MouseMoveEvent:
				Log::LogEvent("MouseMoveEvent: diff = %", mouseMoveEvent.diff);
				break;
			case Type::MouseButtonEvent:
				Log::LogEvent("MouseButtonEvent: button = %, action = %", s_MouseButtonStrings[(uint8_t)mouseButtonEvent.button], s_MouseButtonActionStrings[(uint8_t)mouseButtonEvent.state]);
				break;
			case Type::MouseScrollEvent:
				Log::LogEvent("MouseScrollEvent: xOffset = %, yOffset = %", mouseScrollEvent.xOffset, mouseScrollEvent.yOffset);
				break;
			case Type::KeyboardEvent:
				Log::LogEvent("KeyboardEvent: key = %, action = %", s_KeyStrings[(uint16_t)keyboardEvent.key], s_KeyboardActionString[(uint8_t)keyboardEvent.state]);
				break;
			default:
				break;
			}
		}
	}
	void InitKeyStrings()
	{
		Input::s_KeyStrings[32] = "KEY_SPACE";
		Input::s_KeyStrings[39] = "KEY_APOSTROPHE";
		Input::s_KeyStrings[44] = "KEY_COMMA";
		Input::s_KeyStrings[45] = "KEY_MINUS";
		Input::s_KeyStrings[46] = "KEY_PERIOD";
		Input::s_KeyStrings[47] = "KEY_SLASH";
		Input::s_KeyStrings[48] = "KEY_0";
		Input::s_KeyStrings[49] = "KEY_1";
		Input::s_KeyStrings[50] = "KEY_2";
		Input::s_KeyStrings[51] = "KEY_3";
		Input::s_KeyStrings[52] = "KEY_4";
		Input::s_KeyStrings[53] = "KEY_5";
		Input::s_KeyStrings[54] = "KEY_6";
		Input::s_KeyStrings[55] = "KEY_7";
		Input::s_KeyStrings[56] = "KEY_8";
		Input::s_KeyStrings[57] = "KEY_9";
		Input::s_KeyStrings[59] = "KEY_SEMICOLON";
		Input::s_KeyStrings[61] = "KEY_EQUAL";
		Input::s_KeyStrings[65] = "KEY_A";
		Input::s_KeyStrings[66] = "KEY_B";
		Input::s_KeyStrings[67] = "KEY_C";
		Input::s_KeyStrings[68] = "KEY_D";
		Input::s_KeyStrings[69] = "KEY_E";
		Input::s_KeyStrings[70] = "KEY_F";
		Input::s_KeyStrings[71] = "KEY_G";
		Input::s_KeyStrings[72] = "KEY_H";
		Input::s_KeyStrings[73] = "KEY_I";
		Input::s_KeyStrings[74] = "KEY_J";
		Input::s_KeyStrings[75] = "KEY_K";
		Input::s_KeyStrings[76] = "KEY_L";
		Input::s_KeyStrings[77] = "KEY_M";
		Input::s_KeyStrings[78] = "KEY_N";
		Input::s_KeyStrings[79] = "KEY_O";
		Input::s_KeyStrings[80] = "KEY_P";
		Input::s_KeyStrings[81] = "KEY_Q";
		Input::s_KeyStrings[82] = "KEY_R";
		Input::s_KeyStrings[83] = "KEY_S";
		Input::s_KeyStrings[84] = "KEY_T";
		Input::s_KeyStrings[85] = "KEY_U";
		Input::s_KeyStrings[86] = "KEY_V";
		Input::s_KeyStrings[87] = "KEY_W";
		Input::s_KeyStrings[88] = "KEY_X";
		Input::s_KeyStrings[89] = "KEY_Y";
		Input::s_KeyStrings[90] = "KEY_Z";
		Input::s_KeyStrings[91] = "KEY_LEFT_BRACKET";
		Input::s_KeyStrings[92] = "KEY_BACKSLASH";
		Input::s_KeyStrings[93] = "KEY_RIGHT_BRACKET";
		Input::s_KeyStrings[96] = "KEY_GRAVE_ACCENT";
		Input::s_KeyStrings[256] = "KEY_ESCAPE";
		Input::s_KeyStrings[257] = "KEY_ENTER";
		Input::s_KeyStrings[258] = "KEY_TAB";
		Input::s_KeyStrings[259] = "KEY_BACKSPACE";
		Input::s_KeyStrings[260] = "KEY_INSERT";
		Input::s_KeyStrings[261] = "KEY_DELETE";
		Input::s_KeyStrings[262] = "KEY_RIGHT";
		Input::s_KeyStrings[263] = "KEY_LEFT";
		Input::s_KeyStrings[264] = "KEY_DOWN";
		Input::s_KeyStrings[265] = "KEY_UP";
		Input::s_KeyStrings[266] = "KEY_PAGE_UP";
		Input::s_KeyStrings[267] = "KEY_PAGE_DOWN";
		Input::s_KeyStrings[268] = "KEY_HOME";
		Input::s_KeyStrings[269] = "KEY_END";
		Input::s_KeyStrings[280] = "KEY_CAPS_LOCK";
		Input::s_KeyStrings[281] = "KEY_SCROLL_LOCK";
		Input::s_KeyStrings[282] = "KEY_NUM_LOCK";
		Input::s_KeyStrings[283] = "KEY_PRINT_SCREEN";
		Input::s_KeyStrings[284] = "KEY_PAUSE";
		Input::s_KeyStrings[290] = "KEY_F1";
		Input::s_KeyStrings[291] = "KEY_F2";
		Input::s_KeyStrings[292] = "KEY_F3";
		Input::s_KeyStrings[293] = "KEY_F4";
		Input::s_KeyStrings[294] = "KEY_F5";
		Input::s_KeyStrings[295] = "KEY_F6";
		Input::s_KeyStrings[296] = "KEY_F7";
		Input::s_KeyStrings[297] = "KEY_F8";
		Input::s_KeyStrings[298] = "KEY_F9";
		Input::s_KeyStrings[299] = "KEY_F10";
		Input::s_KeyStrings[300] = "KEY_F11";
		Input::s_KeyStrings[301] = "KEY_F12";
		Input::s_KeyStrings[302] = "KEY_F13";
		Input::s_KeyStrings[303] = "KEY_F14";
		Input::s_KeyStrings[304] = "KEY_F15";
		Input::s_KeyStrings[305] = "KEY_F16";
		Input::s_KeyStrings[306] = "KEY_F17";
		Input::s_KeyStrings[307] = "KEY_F18";
		Input::s_KeyStrings[308] = "KEY_F19";
		Input::s_KeyStrings[309] = "KEY_F20";
		Input::s_KeyStrings[310] = "KEY_F21";
		Input::s_KeyStrings[311] = "KEY_F22";
		Input::s_KeyStrings[312] = "KEY_F23";
		Input::s_KeyStrings[313] = "KEY_F24";
		Input::s_KeyStrings[314] = "KEY_F25";
		Input::s_KeyStrings[320] = "KEY_KEYPAD_0";
		Input::s_KeyStrings[321] = "KEY_KEYPAD_1";
		Input::s_KeyStrings[322] = "KEY_KEYPAD_2";
		Input::s_KeyStrings[323] = "KEY_KEYPAD_3";
		Input::s_KeyStrings[324] = "KEY_KEYPAD_4";
		Input::s_KeyStrings[325] = "KEY_KEYPAD_5";
		Input::s_KeyStrings[326] = "KEY_KEYPAD_6";
		Input::s_KeyStrings[327] = "KEY_KEYPAD_7";
		Input::s_KeyStrings[328] = "KEY_KEYPAD_8";
		Input::s_KeyStrings[329] = "KEY_KEYPAD_9";
		Input::s_KeyStrings[330] = "KEY_KEYPAD_DECIMAL";
		Input::s_KeyStrings[331] = "KEY_KEYPAD_DIVIDE";
		Input::s_KeyStrings[332] = "KEY_KEYPAD_MULTIPLY";
		Input::s_KeyStrings[333] = "KEY_KEYPAD_SUBTRACT";
		Input::s_KeyStrings[334] = "KEY_KEYPAD_ADD";
		Input::s_KeyStrings[335] = "KEY_KEYPAD_ENTER";
		Input::s_KeyStrings[336] = "KEY_KEYPAD_EQUAL";
		Input::s_KeyStrings[340] = "KEY_LEFT_SHIFT";
		Input::s_KeyStrings[341] = "KEY_LEFT_CONTROL";
		Input::s_KeyStrings[342] = "KEY_LEFT_ALT";
		Input::s_KeyStrings[343] = "KEY_LEFT_SUPER";
		Input::s_KeyStrings[344] = "KEY_RIGHT_SHIFT";
		Input::s_KeyStrings[345] = "KEY_RIGHT_CONTROL";
		Input::s_KeyStrings[346] = "KEY_RIGHT_ALT";
		Input::s_KeyStrings[347] = "KEY_RIGHT_SUPER";
		Input::s_KeyStrings[348] = "KEY_MENU";
	}
}