#pragma once
#include "Utils/Filepath.hpp"
#include "PtSceneObj.hpp"
#include <vector>
#include "Core/PtObj.hpp"

namespace Parrot
{
	class PtScene : public PtObj
	{
	public:
		struct Data
		{
			size_t objCount = 0;
			PtSceneObj* objs = nullptr;
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