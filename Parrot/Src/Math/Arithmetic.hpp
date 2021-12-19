#pragma once

namespace Parrot
{
	namespace Math
	{
		template<class T>
		constexpr T Abs(T x) { return x > (T)0 ? x : -x; }

		template<class Arg>
		constexpr Arg Max(Arg a) { return a; }
		template<class Arg1, class Arg2, class... FArgs>
		constexpr Arg1 Max(Arg1 a, Arg2 b, FArgs... fArgs) { return a < b ? (Arg1)Max(b, fArgs...) : (Arg1)Max(a, fArgs...); }

		template<class Arg>
		constexpr Arg Min(Arg a) { return a; }
		template<class Arg1, class Arg2, class... FArgs>
		constexpr Arg1 Min(Arg1 a, Arg2 b, FArgs... fArgs) { return a > b ? (Arg1)Min(b, fArgs...) : (Arg1)Min(a, fArgs...); }

		constexpr float Floor(float x)
		{
			return (float)(int32_t)x;
		}
		constexpr float Ceil(float x)
		{
			return (float)((int32_t)x + 1);
		}
		constexpr float Fract(float x)
		{
			return x - (float)(int32_t)x;
		}
		constexpr double Floor(double x)
		{
			return (double)(int64_t)x;
		}
		constexpr double Ceil(double x)
		{
			return (double)((int64_t)x + 1);
		}
		constexpr double Fract(double x)
		{
			return x - (double)(int64_t)x;
		}

		constexpr float Map(float val, float oldMin, float oldMax, float newMin, float newMax)
		{
			return newMin + (val - oldMin) / (oldMax - oldMin) * (newMax - newMin);
		}
		constexpr double Map(double val, double oldMin, double oldMax, double newMin, double newMax)
		{
			return newMin + (val - oldMin) / (oldMax - oldMin) * (newMax - newMin);
		}
	}
}