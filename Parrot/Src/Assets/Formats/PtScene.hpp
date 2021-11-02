#pragma once
#include "Utils/Filepath.hpp"

namespace Parrot
{
	class PtScene
	{
	public:
		struct Data
		{

		};
	public:
		PtScene(const Utils::Filepath& filepath);

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}