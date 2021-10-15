#pragma once
#include "Ptpch.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	class SceneObject
	{
	private:
		const char* m_Name;
	public:
		SceneObject() = delete;

		template<class _Type>
		_Type AddComponent();
		template<class _Type>
		void RemoveComponent();
		template<class _Type>
		_Type GetComponent();
	};
}