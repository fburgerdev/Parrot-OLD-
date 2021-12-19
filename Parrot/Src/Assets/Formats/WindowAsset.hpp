#pragma once
#include "Core/PtObj.hpp"
#include "Math/Vector.hpp"
#include "Utils/Filepath.hpp"
#include "SceneAsset.hpp"

namespace Parrot
{
	class Constructor;
	namespace Asset
	{
		class WindowAsset : public PtObj
		{
		private:
			WindowAsset(const Utils::Filepath& filepath);
			friend Constructor;
		public:
			const SceneAsset* scene;
			Math::Vec2u size = Math::Vec2u(1080, 720);
			std::string style = "default";
		};
	}
}
