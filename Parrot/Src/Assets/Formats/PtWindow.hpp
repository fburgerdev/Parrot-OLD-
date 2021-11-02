#pragma once
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	class PtWindow
	{
	public:
		struct Data
		{
			std::string defaultScene;
			Math::Vec2u size;
		};
	public:
		PtWindow(const Utils::Filepath& filepath);

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}
