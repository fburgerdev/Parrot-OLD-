#pragma once
#include "Core/Core.hpp"
#include "DebugMsg.hpp"
#include "Math/Matrix.hpp"

#include <ostream>

namespace Parrot
{
	class Debugstream
	{
	public:
		Debugstream(Uninitialized);

		Debugstream& operator<<(char ch);
		Debugstream& operator<<(const char* arg);
		Debugstream& operator<<(Debugstream& (*func)(Debugstream&));
		template<class T, size_t Dim>
		Debugstream& operator<<(const Math::SqrMat<T, Dim>& mat)
		{
			if (!m_ActiveMsg)
				StartMsg(DebugMsg::Type::Info);
			if (m_IsCout)
				*m_Ostream << std::setprecision(4);
			PutCh('\n');
			for (size_t i = 0; i < Dim; ++i)
			{
				for (size_t j = 0; j < Dim; ++j)
				{
					this->operator<<(mat.Raw[Dim * j + i]);
					PutCh('\t');
				}
				PutCh('\n');
			}
			if (m_IsCout)
				*m_Ostream << std::fixed;
			return *this;
		}

		template<class T>
		Debugstream& operator<<(const T& arg)
		{
			if (!m_ActiveMsg)
				StartMsg(DebugMsg::Type::Info);

			if (m_Ostream)
				*m_Ostream << arg;
			if (m_Fstream)
				*m_Fstream << arg;
			return *this;
		}
		template<> 
		Debugstream& operator<<(const std::string& arg);
		template<>
		Debugstream& operator<<(const DebugMsg& msg);

		static Debugstream& EndMsg(Debugstream& stream);
	private:
		void PutCh(char ch);
		void PutCStr(const char* str);

		void Init(std::ostream* ostream, std::ofstream* ofstream);
		friend void OnCreate();

		void StartMsg(DebugMsg::Type type);
		void Indent();
	private:
		bool m_IsCout = false;
		std::ostream* m_Ostream;
		std::ofstream* m_Fstream;

		size_t m_MsgCount = 0;
		bool m_ActiveMsg = false;
	};

	extern Debugstream DebugOut;
}