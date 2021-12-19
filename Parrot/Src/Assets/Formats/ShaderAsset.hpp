#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"

namespace Parrot
{
	class Constructor;
	namespace Asset
	{
		class ShaderAsset : public PtObj
		{
		private:
			ShaderAsset(const Utils::Filepath& filepath);
			ShaderAsset(const std::string& tag);
			friend Constructor;
		public:
			void SaveToFile(const Utils::Filepath& filepath);
		public:
			std::string vertexSrc;
			std::string fragmentSrc;
		};
	}
}
