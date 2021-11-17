#pragma once
#include "Utils/Filepath.hpp"
#include "Graphics/GraphicsAPI.hpp"

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
		~PtShader();

		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
		const ShaderAPI& GetShaderAPI();
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
		ShaderAPI* m_ShaderAPI = nullptr;
	};
}
