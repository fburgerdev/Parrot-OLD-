#pragma once
#include "Core/PtObj.hpp"
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"
#include "Graphics/GraphicsAPI.hpp"

namespace Parrot
{
	class Constructor;
	namespace Asset
	{
		class TexAsset : public PtObj
		{
		private:
			TexAsset(const Utils::Filepath& filepath);
			TexAsset(const std::string& tag);
			friend Constructor;
		public:
			~TexAsset();
			
			Math::Vec4u8& Pixel(Math::Vec2u coords) const;
			void SaveToFile(const Utils::Filepath& filepath);
			void LoadImage();
		public:
			Utils::Filename image;
			Graphics::TextureAPI::Settings settings;
			Math::Vec2u size;
			Math::Vec4u8* buffer = nullptr;
		};
	}
}