#include "Ptpch.hpp"
#include "PtObj.hpp"

namespace Parrot
{
	PtObj::PtObj(PtObj::Type type)
		: m_ID(++s_IDCount), m_Type(type)
	{
		++s_ObjCount[(int8_t)type];
	}
	PtObj::~PtObj()
	{
		--s_ObjCount[(int8_t)m_Type];
	}
	uint64_t PtObj::ID() const
	{
		return m_ID;
	}

	uint64_t PtObj::s_IDCount = 0;
	uint64_t PtObj::s_ObjCount[9] = { 0 };
}