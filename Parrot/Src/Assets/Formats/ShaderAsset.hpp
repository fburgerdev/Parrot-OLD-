#pragma once
#include "Utils/Filepath.hpp"
#include "Graphics/GraphicsAPI.hpp"
#include "Core/PtObj.hpp"

namespace Parrot
{
	namespace Asset
	{
		class ShaderAsset : public PtObj
		{
		public:
			struct Data
			{
				std::string vertexSrc;
				std::string fragmentSrc;
			};
		public:
			ShaderAsset(const Utils::Filepath& filepath);
			~ShaderAsset();

			const Utils::Filepath& GetFilepath() const;
			const Data& GetData() const;
		private:
			Utils::Filepath m_Filepath;
			Data m_Data;
		};
	}
}
