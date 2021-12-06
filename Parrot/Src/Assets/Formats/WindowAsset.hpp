#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"
#include "SceneAsset.hpp"

namespace Parrot
{
	namespace Asset
	{
		class WindowAsset : public PtObj
		{
		public:
			WindowAsset(const Utils::Filepath& filepath);
		public:
			Utils::Filepath filepath;

			const SceneAsset* scene;
			Math::Vec2u size = Math::Vec2u(1080, 720);
			std::string style = "default";
		};
	}
}
