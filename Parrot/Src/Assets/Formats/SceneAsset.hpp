#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "SceneObjAsset.hpp"

#include <vector>

namespace Parrot
{
	class Constructor;
	namespace Asset
	{
		class SceneAsset : public PtObj
		{
		private:
			SceneAsset(const Utils::Filepath& filepath);
			friend Constructor;
		public:
			std::vector<SceneObjAsset*> sceneObjAssets;
		};
	}
}