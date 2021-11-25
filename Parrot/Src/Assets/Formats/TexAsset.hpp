#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	namespace Asset
	{
		class TexAsset : public PtObj
		{
			struct Data
			{
				Graphics::TextureAPI::Settings settings;
				Math::Vec2u size;
				uint8_t* buffer = nullptr;
			};
		public:
			TexAsset(const Utils::Filepath& filepath);
			~TexAsset();

			const Utils::Filepath& GetFilepath() const;
			const Data& GetData() const;
		private:
			Utils::Filepath m_Filepath;
			Data m_Data;
		};
	}
}