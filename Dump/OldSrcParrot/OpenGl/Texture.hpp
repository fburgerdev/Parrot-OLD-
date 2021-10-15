#pragma once
#include "Pch.hpp"
#include "Vector.hpp"

namespace Parrot
{
	class Texture
	{
	public:
		struct Config
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
		enum class ColorFormat : int32_t
		{
			RGB = 0x1907, RGBA = 0x1908, Red = 0x1903, Green = 0x1904, Blue = 0x1905
		};
	private:
		static const Config s_DefaultConfig;

		uint32_t m_ID;
		Vector::Vec2u m_Dim;
	public:
		Texture(const std::string& path, const Config& config = s_DefaultConfig);
		Texture(const uint8_t* buffer, Vector::Vec2u dim, ColorFormat colorFormat, const Config& config);
		Texture() : m_ID(0), m_Dim(0) {};
		~Texture();

		bool LoadTextureFromPath(const std::string& path, const Config& config = s_DefaultConfig);
		void LoadTexture(const uint8_t* buffer, Vector::Vec2u dim, ColorFormat colorFormat, const Config& config);

		uint32_t GetID() const { return m_ID; }

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;

		Vector::Vec2u GetDim() const { return m_Dim; }
	};
}