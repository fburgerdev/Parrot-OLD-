#pragma once
#include "Utils/Filepath.hpp"

namespace Parrot
{
	class PtShader
	{
	public:
		struct Data
		{
			std::string vertexSrc;
			std::string fragmentSrc;
		};
	public:
		PtShader(const Utils::Filepath& filepath);

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}
