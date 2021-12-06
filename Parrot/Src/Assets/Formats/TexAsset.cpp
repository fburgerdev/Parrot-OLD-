#include "Ptpch.hpp"
#include "TexAsset.hpp"

#include "Debug/Internal_Log.hpp"
#include "Assets/Internal_AssetManager.hpp"

namespace Parrot
{
	namespace Asset
	{
		TexAsset::TexAsset(const Utils::Filepath& filepath)
			: PtObj(PtObj::Type::TexAsset), filepath(filepath)
		{
			std::ifstream stream(filepath.FullPath(), std::ios::binary);
			Internal_Log::LogAssert(stream.is_open(), "File \"%\" could not be opened. Either the file doesn't exist or it is already opened by another process.", filepath.FullPath());
			std::string line;
			std::getline(stream, line);
			imageFilename = line;
			stream.read((char*)&settings, sizeof(Graphics::TextureAPI::Settings));
			//stream.read((char*)&size, sizeof(Math::Vec2u));
			//buffer = new Math::Vec4u8[(size_t)size.x * (size_t)size.y];
			//stream.read((char*)buffer, (size_t)size.x * (size_t)size.y * 4);
			stream.close();
			LoadImage();
		}
		TexAsset::TexAsset()
			: PtObj(PtObj::Type::TexAsset)
		{

		}
		TexAsset::~TexAsset()
		{
			delete[] buffer;
		}
		
		uint32_t TexAsset::BufferIndex(Math::Vec2u coords)
		{
			return coords.y * size.x + coords.x;
		}

		void TexAsset::SaveToFile()
		{
			std::ofstream stream(filepath.FullPath(), std::ios::binary);
			stream.write(imageFilename.String().c_str(), imageFilename.String().length());
			stream.write("\n", 1);
			stream.write((char*)&settings, sizeof(Graphics::TextureAPI::Settings));
			/*stream.write((char*)&size, sizeof(Math::Vec2u));
			stream.write((char*)buffer, (size_t)size.x * (size_t)size.y * 4);*/
			stream.close();
		}

		void TexAsset::LoadImage()
		{
			Internal_AssetManager::LoadImageFromFilename(imageFilename, size, buffer);
		}
	}
}