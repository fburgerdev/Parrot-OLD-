#include "Ptpch.hpp"
#include "PtObj.hpp"

namespace Parrot
{
	PtObj::PtObj(PtObjType type)
		: m_ID(++s_ObjCount[(int8_t)type])
	{

	}

	uint64_t PtObj::GetObjID() const
	{
		return m_ID;
	}
	
	uint64_t PtObj::s_ObjCount[9] = { ((uint64_t)1 << 62), ((uint64_t)1 << 61), ((uint64_t)1 << 60), ((uint64_t)1 << 59), ((uint64_t)1 << 58), ((uint64_t)1 << 57), ((uint64_t)1 << 56), ((uint64_t)1 << 55), ((uint64_t)1 << 54) };
}