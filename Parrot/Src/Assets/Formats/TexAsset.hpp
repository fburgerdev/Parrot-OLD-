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
		public:
			TexAsset(const Utils::Filepath& filepath);
			TexAsset();
			~TexAsset();

			uint32_t BufferIndex(Math::Vec2u coords);
			void SaveToFile();
		public:
			Utils::Filepath filepath;

			Graphics::TextureAPI::Settings settings;
			Math::Vec2u size;
			Math::Vec4u8* buffer = nullptr;
		};
	}
}