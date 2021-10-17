#include "Ptpch.hpp"
#include "SceneObject.hpp"

namespace Parrot
{
	SceneObject::SceneObject(const std::string& tag)
		: m_Tag(tag)
	{

	}
	SceneObject::~SceneObject()
	{

	}

	const std::string& SceneObject::GetTag() const
	{
		return m_Tag;
	}
}
