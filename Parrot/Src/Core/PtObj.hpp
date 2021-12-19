#pragma once
#include <memory>
#include <string>

namespace Parrot
{
	class PtObj
	{
	public:
		size_t GetID() const;
		const std::string& GetTag() const;
	protected:
		PtObj(std::string_view tag);
		PtObj(std::string&& tag) noexcept;
		PtObj();
		virtual ~PtObj();
		std::string m_Tag;
	private:
		size_t m_ID;
	};
	
	PtObj& GetPtObj(size_t id);
}