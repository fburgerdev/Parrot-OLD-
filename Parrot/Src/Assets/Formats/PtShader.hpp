#pragma once
#include "Utils/Filepath.hpp"
#include "Graphics/GraphicsAPI.hpp"
#include "Core/PtObj.hpp"

namespace Parrot
{
	class PtShader : public PtObj
	{
	public:
		struct Data
		{
			std::string vertexSrc;
			std::string fragmentSrc;
		};
	public:
		PtShader(const Utils::Filepath& filepath);
		~PtShader();

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}
