#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"

#include <vector>

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

			std::vector<void*> sceneObjs;
		};
	}
}