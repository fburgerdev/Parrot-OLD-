#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "SceneObjAsset.hpp"

namespace Parrot
{
	namespace Asset
	{
		class SceneAsset : public PtObj
		{
		public:
			SceneAsset(const Utils::Filepath& filepath);
		public:
			Utils::Filepath filepath;

			size_t objCount = 0;
			SceneObjAsset* objs = nullptr;
		};
	}
}