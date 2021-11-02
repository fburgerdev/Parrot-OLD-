#pragma once
#include "Utils/Filepath.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	class PtTex
	{
	public:
		struct Settings
		{
			enum class Wrap : int32_t
			{
				ClampToEdge = 0x812F, ClampToBorder = 0x812D, Repeat = 0x2901, MirroredRepeat = 0x8370
			};
			enum class Filter : int32_t
			{
				Linear = 0x2601, Nearest = 0x2600
			};
			enum class Mipmap : uint8_t
			{
				None, Linear, Nearest
			};
			Wrap horWrap = Wrap::ClampToEdge;
			Wrap verWrap = Wrap::ClampToEdge;
			Filter magFilter = Filter::Linear;
			Filter minFilter = Filter::Linear;
			Mipmap mipmap = Mipmap::None;
		};
		struct Data
		{
			Settings settings;
			Math::Vec2u size;
			uint8_t* buffer;
		};
	public:
		PtTex(const Utils::Filepath& filepath);
		~PtTex();
		
		const Utils::Filepath& GetFilepath() const;
		const Data& GetData() const;
	private:
		Utils::Filepath m_Filepath;
		Data m_Data;
	};
}