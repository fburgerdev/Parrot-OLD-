#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	namespace Asset
	{
		class WindowAsset : public PtObj
		{
		public:
			struct Data
			{
				std::string scene;
				Math::Vec2u size = Math::Vec2u(1080, 720);
				std::string style = "default";
			};
		public:
			WindowAsset(const Utils::Filepath& filepath);

			const Utils::Filepath& GetFilepath() const;
			const Data& GetData() const;
		private:
			Utils::Filepath m_Filepath;
			Data m_Data;
		};
	}
}
