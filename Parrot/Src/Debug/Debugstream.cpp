#include "Ptpch.hpp"
#include "DebugStream.hpp"

#include "Console.hpp"

namespace Parrot
{
	Debugstream::Debugstream(Uninitialized)
		: m_Ostream(nullptr), m_Fstream(nullptr) { }

	Debugstream& Debugstream::operator<<(char ch)
	{
		if (!m_ActiveMsg)
			StartMsg(DebugMsg::Type::Info);

		PutCh(ch);
		return *this;
	}
	Debugstream& Debugstream::operator<<(const char* arg)
	{
		if (!m_ActiveMsg)
			StartMsg(DebugMsg::Type::Info);

		PutCStr(arg);
		return *this;
	}
	template<>
	Debugstream& Debugstream::operator<<(const std::string& arg)
	{
		if (!m_ActiveMsg)
			StartMsg(DebugMsg::Type::Info);

		PutCStr(arg.c_str());
		return *this;
	}
	Debugstream& Debugstream::operator<<(Debugstream& (*func)(Debugstream&))
	{
		func(*this);
		return *this;
	}

	void Debugstream::Init(std::ostream* ostream, std::ofstream* ofstream)
	{
		m_IsCout = ostream == &std::cout;
		m_Ostream = ostream;
		m_Fstream = ofstream;
	}

	void Debugstream::Indent()
	{
		PutCStr("\t\t\t");
	}

	template<>
	Debugstream& Debugstream::operator<<(const DebugMsg& error)
	{
		if (m_ActiveMsg)
			operator<<(Debugstream::EndMsg);
		StartMsg(error.type);
		
		PutCStr(error.name);
		PutCh('|');
		PutCStr(std::to_string(error.code).c_str());
		PutCStr(": ");
		PutCStr(error.explanation);
		PutCh('\n');
		m_ActiveMsg = true;
		return *this;
	}
	Debugstream& Debugstream::EndMsg(Debugstream& stream)
	{
		if (stream.m_Ostream)
			*stream.m_Ostream << std::endl;
		if (stream.m_Fstream)
			*stream.m_Fstream << std::endl;
		stream.m_ActiveMsg = false;
		return stream;
	}

	void Debugstream::StartMsg(DebugMsg::Type type)
	{
		if (m_IsCout)
		{
			if (type == DebugMsg::Type::Info)
				Console::SetColor(Console::Color::White);
			else if (type == DebugMsg::Type::Warning)
				Console::SetColor(Console::Color::Yellow);
			else if (type == DebugMsg::Type::Error)
				Console::SetColor(Console::Color::Red);
		}
		PutCh('(');
		PutCStr(std::to_string(++m_MsgCount).c_str());
		PutCStr(")\t");
		if (type == DebugMsg::Type::Info)
			PutCStr("[INFO]\t\t");
		else if (type == DebugMsg::Type::Warning)
			PutCStr("[WARNING]\t");
		else if (type == DebugMsg::Type::Error)
			PutCStr("[Error]\t\t");
		m_ActiveMsg = true;
	}

	void Debugstream::PutCh(char ch)
	{
		if (m_Ostream)
			*m_Ostream << ch;
		if (m_Fstream)
			*m_Fstream << ch;
		if (ch == '\n')
			Indent();
	}
	void Debugstream::PutCStr(const char* str)
	{
		while (*str != '\0')
			PutCh(*str++);
	}

	Debugstream DebugOut({});
}