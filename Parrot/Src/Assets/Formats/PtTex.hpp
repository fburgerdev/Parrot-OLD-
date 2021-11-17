#pragma once
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	class PtTex
	{
		struct Data
		{
			TextureAPI::Settings settings;
			Math::Vec2u size;
			uint8_t* buffer = nullptr;
		};
	public:
		PtTex(const Utils::Filepath& filepath);
		~PtTex();
		
		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
		void BindTexture() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;

		mutable TextureAPI* m_TextureAPI = nullptr;
	};
}