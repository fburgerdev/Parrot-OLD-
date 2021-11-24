#pragma once
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"
#include "Core/PtObj.hpp"

namespace Parrot
{
	class PtWindow : public PtObj
	{
	public:
		struct Data
		{
			std::string scene;
			Math::Vec2u size = Math::Vec2u(1080, 720);
			std::string style = "default";
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
