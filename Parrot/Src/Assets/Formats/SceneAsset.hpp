#pragma once
#include "SceneObjAsset.hpp"
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	namespace Asset
	{
		class SceneAsset : public PtObj
		{
		public:
			struct Data
			{
				size_t objCount = 0;
				SceneObjAsset* objs = nullptr;
			};
		public:
			SceneAsset(const Utils::Filepath& filepath);

			const Utils::Filepath& GetFilepath() const;
			const Data& GetData() const;
		private:
			Utils::Filepath m_Filepath;
			Data m_Data;
		};
	}
}