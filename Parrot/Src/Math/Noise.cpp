#include "Ptpch.hpp"
#include "Noise.hpp"

#include "Random.hpp"
#include "Arithmetic.hpp"

namespace Parrot
{
	namespace Math
	{
		static constexpr size_t s_PerlinOctaves = 10;
		static constexpr size_t s_PerlinSampleSize = (1 << s_PerlinOctaves);
		static float* perlin1D;
		static float* perlin1D2;


		/*
		4
		| | | | | | | | |
		|   |   |   |   |
		|       |       |
		|               |
		0 1 2 3 4 5 6 7 8
		*/
		static void CreatePerlin(float*& perlin)
		{
			float* rands = new float[s_PerlinSampleSize];
			for (size_t i = 0; i < s_PerlinSampleSize; ++i)
				rands[i] = Randf();

			perlin = new float[s_PerlinSampleSize];
			memset(perlin, 0, sizeof(float) * s_PerlinSampleSize);

			for (size_t octave = 0; octave <= s_PerlinOctaves; ++octave)
			{
				float significance = 0.5f / pow(2, octave);
				size_t step = ((size_t)1 << (s_PerlinOctaves - octave));

				perlin[0] += significance * rands[0];
				for (size_t sample = 1; sample < s_PerlinSampleSize - 1; ++sample)
				{
					size_t leftIndex = step * (sample / step);
					float interpolation = (float)(sample - leftIndex) / step;
					perlin[sample] += significance * ((1.0f - interpolation) * rands[leftIndex] + interpolation * rands[(leftIndex + step) % s_PerlinSampleSize]);
				}
				perlin[s_PerlinSampleSize - 1] += significance * rands[s_PerlinSampleSize - 1];
			}

			delete[] rands;
		}

		void InitNoise(size_t seed)
		{
			srand(seed);
			CreatePerlin(perlin1D);
			srand(seed + rand());
			CreatePerlin(perlin1D2);
		}

		float PerlinNoise(float offset)
		{
			return perlin1D[(size_t)offset % s_PerlinSampleSize] * (1.0f - Fract(offset)) + perlin1D[((size_t)offset + 1) % s_PerlinSampleSize] * Fract(offset);
		}

		float Perlin2D(Vec2f offset)
		{
			return	(perlin1D[(size_t)offset.x % s_PerlinSampleSize] * (1.0f - Fract(offset.x)) + perlin1D[((size_t)offset.x + 1) % s_PerlinSampleSize] * Fract(offset.x) +
				perlin1D2[(size_t)offset.y % s_PerlinSampleSize] * (1.0f - Fract(offset.y)) + perlin1D2[((size_t)offset.y + 1) % s_PerlinSampleSize] * Fract(offset.y)) / 2;
		}
	}
}