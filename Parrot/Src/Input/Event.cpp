#include "Ptpch.hpp"
#include "Debug/Log.hpp"
#include "Event.hpp"

namespace Parrot
{
	static constexpr const char* s_MouseButtonStrings[3] = { "Left", "Right", "Middle" };
	static constexpr const char* s_MouseButtonActionStrings[2] = { "Release", "Press" };
	static constexpr const char* s_KeyboardActionString[3] = { "Release", "Press", "Repeat" };
	static const char* s_KeyStrings[350];
	void InitKeyStrings()
	{
		s_KeyStrings[32] = "KEY_SPACE";
		s_KeyStrings[39] = "KEY_APOSTROPHE";
		s_KeyStrings[44] = "KEY_COMMA";
		s_KeyStrings[45] = "KEY_MINUS";
		s_KeyStrings[46] = "KEY_PERIOD";
		s_KeyStrings[47] = "KEY_SLASH";
		s_KeyStrings[48] = "KEY_0";
		s_KeyStrings[49] = "KEY_1";
		s_KeyStrings[50] = "KEY_2";
		s_KeyStrings[51] = "KEY_3";
		s_KeyStrings[52] = "KEY_4";
		s_KeyStrings[53] = "KEY_5";
		s_KeyStrings[54] = "KEY_6";
		s_KeyStrings[55] = "KEY_7";
		s_KeyStrings[56] = "KEY_8";
		s_KeyStrings[57] = "KEY_9";
		s_KeyStrings[59] = "KEY_SEMICOLON";
		s_KeyStrings[61] = "KEY_EQUAL";
		s_KeyStrings[65] = "KEY_A";
		s_KeyStrings[66] = "KEY_B";
		s_KeyStrings[67] = "KEY_C";
		s_KeyStrings[68] = "KEY_D";
		s_KeyStrings[69] = "KEY_E";
		s_KeyStrings[70] = "KEY_F";
		s_KeyStrings[71] = "KEY_G";
		s_KeyStrings[72] = "KEY_H";
		s_KeyStrings[73] = "KEY_I";
		s_KeyStrings[74] = "KEY_J";
		s_KeyStrings[75] = "KEY_K";
		s_KeyStrings[76] = "KEY_L";
		s_KeyStrings[77] = "KEY_M";
		s_KeyStrings[78] = "KEY_N";
		s_KeyStrings[79] = "KEY_O";
		s_KeyStrings[80] = "KEY_P";
		s_KeyStrings[81] = "KEY_Q";
		s_KeyStrings[82] = "KEY_R";
		s_KeyStrings[83] = "KEY_S";
		s_KeyStrings[84] = "KEY_T";
		s_KeyStrings[85] = "KEY_U";
		s_KeyStrings[86] = "KEY_V";
		s_KeyStrings[87] = "KEY_W";
		s_KeyStrings[88] = "KEY_X";
		s_KeyStrings[89] = "KEY_Y";
		s_KeyStrings[90] = "KEY_Z";
		s_KeyStrings[91] = "KEY_LEFT_BRACKET";
		s_KeyStrings[92] = "KEY_BACKSLASH";
		s_KeyStrings[93] = "KEY_RIGHT_BRACKET";
		s_KeyStrings[96] = "KEY_GRAVE_ACCENT";
		s_KeyStrings[256] = "KEY_ESCAPE";
		s_KeyStrings[257] = "KEY_ENTER";
		s_KeyStrings[258] = "KEY_TAB";
		s_KeyStrings[259] = "KEY_BACKSPACE";
		s_KeyStrings[260] = "KEY_INSERT";
		s_KeyStrings[261] = "KEY_DELETE";
		s_KeyStrings[262] = "KEY_RIGHT";
		s_KeyStrings[263] = "KEY_LEFT";
		s_KeyStrings[264] = "KEY_DOWN";
		s_KeyStrings[265] = "KEY_UP";
		s_KeyStrings[266] = "KEY_PAGE_UP";
		s_KeyStrings[267] = "KEY_PAGE_DOWN";
		s_KeyStrings[268] = "KEY_HOME";
		s_KeyStrings[269] = "KEY_END";
		s_KeyStrings[280] = "KEY_CAPS_LOCK";
		s_KeyStrings[281] = "KEY_SCROLL_LOCK";
		s_KeyStrings[282] = "KEY_NUM_LOCK";
		s_KeyStrings[283] = "KEY_PRINT_SCREEN";
		s_KeyStrings[284] = "KEY_PAUSE";
		s_KeyStrings[290] = "KEY_F1";
		s_KeyStrings[291] = "KEY_F2";
		s_KeyStrings[292] = "KEY_F3";
		s_KeyStrings[293] = "KEY_F4";
		s_KeyStrings[294] = "KEY_F5";
		s_KeyStrings[295] = "KEY_F6";
		s_KeyStrings[296] = "KEY_F7";
		s_KeyStrings[297] = "KEY_F8";
		s_KeyStrings[298] = "KEY_F9";
		s_KeyStrings[299] = "KEY_F10";
		s_KeyStrings[300] = "KEY_F11";
		s_KeyStrings[301] = "KEY_F12";
		s_KeyStrings[302] = "KEY_F13";
		s_KeyStrings[303] = "KEY_F14";
		s_KeyStrings[304] = "KEY_F15";
		s_KeyStrings[305] = "KEY_F16";
		s_KeyStrings[306] = "KEY_F17";
		s_KeyStrings[307] = "KEY_F18";
		s_KeyStrings[308] = "KEY_F19";
		s_KeyStrings[309] = "KEY_F20";
		s_KeyStrings[310] = "KEY_F21";
		s_KeyStrings[311] = "KEY_F22";
		s_KeyStrings[312] = "KEY_F23";
		s_KeyStrings[313] = "KEY_F24";
		s_KeyStrings[314] = "KEY_F25";
		s_KeyStrings[320] = "KEY_KEYPAD_0";
		s_KeyStrings[321] = "KEY_KEYPAD_1";
		s_KeyStrings[322] = "KEY_KEYPAD_2";
		s_KeyStrings[323] = "KEY_KEYPAD_3";
		s_KeyStrings[324] = "KEY_KEYPAD_4";
		s_KeyStrings[325] = "KEY_KEYPAD_5";
		s_KeyStrings[326] = "KEY_KEYPAD_6";
		s_KeyStrings[327] = "KEY_KEYPAD_7";
		s_KeyStrings[328] = "KEY_KEYPAD_8";
		s_KeyStrings[329] = "KEY_KEYPAD_9";
		s_KeyStrings[330] = "KEY_KEYPAD_DECIMAL";
		s_KeyStrings[331] = "KEY_KEYPAD_DIVIDE";
		s_KeyStrings[332] = "KEY_KEYPAD_MULTIPLY";
		s_KeyStrings[333] = "KEY_KEYPAD_SUBTRACT";
		s_KeyStrings[334] = "KEY_KEYPAD_ADD";
		s_KeyStrings[335] = "KEY_KEYPAD_ENTER";
		s_KeyStrings[336] = "KEY_KEYPAD_EQUAL";
		s_KeyStrings[340] = "KEY_LEFT_SHIFT";
		s_KeyStrings[341] = "KEY_LEFT_CONTROL";
		s_KeyStrings[342] = "KEY_LEFT_ALT";
		s_KeyStrings[343] = "KEY_LEFT_SUPER";
		s_KeyStrings[344] = "KEY_RIGHT_SHIFT";
		s_KeyStrings[345] = "KEY_RIGHT_CONTROL";
		s_KeyStrings[346] = "KEY_RIGHT_ALT";
		s_KeyStrings[347] = "KEY_RIGHT_SUPER";
		s_KeyStrings[348] = "KEY_MENU";
	}

	void Parrot::Event::Log() const
	{
		switch (type)
		{
		case Type::WindowResizeEvent:
			Log::LogEvent("WindowResizeEvent: dim = %", windowResizeEvent.dim);
			break;
		case Type::WindowCloseRequestEvent:
			Log::LogEvent("WindowCloseRequestEvent:");
			break;
		case Type::WindowMaximizeEvent:
			Log::LogEvent("WindowMaximizeEvent:");
			break;
		case Type::MouseMoveEvent:
			Log::LogEvent("MouseMoveEvent: pos = %", mouseMoveEvent.pos);
			break;
		case Type::MouseButtonEvent:
			Log::LogEvent("MouseButtonEvent: button = %, action = %", s_MouseButtonStrings[(uint8_t)mouseButtonEvent.button], s_MouseButtonActionStrings[(uint8_t)mouseButtonEvent.state]);
			break;
		case Type::MouseScrollEvent:
			Log::LogEvent("MouseScrollEvent: xOffset = %, yOffset = %", mouseScrollEvent.xOffset, mouseScrollEvent.yOffset);
			break;
		case Type::KeyboardEvent:
			Log::LogEvent("KeyboardEvent: key = %, action = %", s_KeyStrings[(uint16_t)keyboardEvent.keyCode], s_KeyboardActionString[(uint8_t)keyboardEvent.state]);
			break;
		default:
			break;
		}
	}

	static std::deque<Event> s_EventQueue;
	bool EventsInQueue()
	{
		return !s_EventQueue.empty();
	}
	Event PollEvent()
	{
		Event e = s_EventQueue.front();
		s_EventQueue.pop_front();
		return e;
	}

	void PushEvent(Event e)
	{
		s_EventQueue.push_back(e);
	}
}