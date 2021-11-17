#pragma once
#include "Utils/Filepath.hpp"
#include "PtSceneObject.hpp"
#include <vector>

namespace Parrot
{
	class PtScene
	{
	public:
		struct Data
		{
			size_t objCount = 0;
			PtSceneObject* objs = nullptr;
		};
	public:
		PtScene(const Utils::Filepath& filepath);

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}