#include "Ptpch.hpp"
#include "Arithmetic.hpp"

namespace Parrot
{
	namespace Math
	{
		float QuakeInverseSquareRoot(float number)
		{
			long i;
			float y;

			y = number;
			i = *(uint32_t*)&y;
			i = 0x5f3759df - (i >> 1);
			y = *(float*)&i;
			return y * (1.5f - (number * 0.5f * y * y));
		}

		float QuakeSquareRoot(float number)
		{
			return QuakeInverseSquareRoot(number * number);
		}
	}
}