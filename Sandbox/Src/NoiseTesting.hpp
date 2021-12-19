#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class NoiseTesting : public Component::Script
{
public:
	using Script::Script;

	virtual void OnCreate() override
	{
	/*	Math::InitNoise(0);
		Asset::TexAsset& tex = AssetManager::CreateTexAsset("Noise");
		tex.size = Math::Vec2u(1024);
		tex.buffer = new Math::Vec4u8[(size_t)tex.size.x * (size_t)tex.size.y];
		for (uint32_t y = 0; y < tex.size.y; y++)
		{
			for (uint32_t x = 0; x < tex.size.x; x++)
			{
				tex.Pixel({ x, y }).rgb = Math::Vec3u8((uint8_t)(Math::PerlinNoise((float)x) * 255.0f));
				tex.Pixel({ x, y }).a = 255;
			}
		}
		
		sceneObj.AddComponent<Component::RenderObj>(AssetManager::GetQuadMesh(), tex);*/
	}
};

