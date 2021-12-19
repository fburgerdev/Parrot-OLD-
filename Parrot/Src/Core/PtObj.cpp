#include "Ptpch.hpp"
#include "PtObj.hpp"

namespace Parrot
{
	static size_t s_IDCount = 0;
	static std::unordered_map<size_t, PtObj*> s_IDMap;

	PtObj::PtObj(const std::string_view tag)
		: m_ID(++s_IDCount), m_Tag(tag)
	{
		s_IDMap[m_ID] = this;
	}		
	PtObj::PtObj(std::string&& tag) noexcept
		: m_ID(++s_IDCount), m_Tag(std::move(tag))
	{
		s_IDMap[m_ID] = this;
	}
	PtObj::PtObj()
		: m_ID(++s_IDCount)
	{
		s_IDMap[m_ID] = this;
	}
	PtObj::~PtObj()
	{
		s_IDMap.erase(m_ID);
	}
	const std::string& PtObj::GetTag() const
	{
		return m_Tag;
	}
	size_t PtObj::GetID() const
	{
		return m_ID;
	}
	
	PtObj& GetPtObj(uint64_t id)
	{
		return *s_IDMap[id];
	}
}