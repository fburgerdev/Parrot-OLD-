#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	namespace Asset
	{
		class ShaderAsset : public PtObj
		{
		public:
			ShaderAsset(const Utils::Filepath& filepath);
			ShaderAsset();

			void SaveToFile();
		public:
			Utils::Filepath filepath;

			std::string vertexSrc;
			std::string fragmentSrc;
		};
	}
}
