#include "Ptpch.hpp"
#include "TexAsset.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	void Internal_LoadImageFromFilename(const Utils::Filename& filename, Math::Vec2u& size, Math::Vec4u8*& buffer);
	namespace Asset
	{
		TexAsset::TexAsset(const Utils::Filepath& filepath)
			: PtObj(filepath.GetFilename().GetName())
		{
			std::ifstream stream(filepath.FullPath(), std::ios::binary);
			if (PT_FUNC_GUARDS_ENABLED && !stream.is_open())
			{
				DebugOut << FileContextWarning << filepath.FullPath() << Debugstream::EndMsg;
				stream.close();
				return;
			}			
			std::string line;
			std::getline(stream, line);
			image = line;
			stream.read((char*)&settings, sizeof(Graphics::TextureAPI::Settings));
			stream.close();
			LoadImage();
		}
		TexAsset::TexAsset(const std::string& tag)
			: PtObj(tag) {}

		TexAsset::~TexAsset()
		{
			delete[] buffer;
		}
		
		Math::Vec4u8& TexAsset::Pixel(Math::Vec2u coords) const
		{
			return buffer[coords.y * size.x + coords.x];
		}

		void TexAsset::SaveToFile(const Utils::Filepath& filepath)
		{
			std::ofstream stream(filepath.FullPath(), std::ios::binary);
			stream.write(image.Str().data(), image.Str().length());
			stream.write("\n", 1);
			stream.write((char*)&settings, sizeof(Graphics::TextureAPI::Settings));
			stream.close();
		}

		void TexAsset::LoadImage()
		{
			Internal_LoadImageFromFilename(image, size, buffer);
		}
	}
}