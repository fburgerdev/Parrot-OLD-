#pragma once

namespace Parrot
{
	namespace Math
	{
		template<class Arg>
		Arg Max(Arg a) { return a; }
		template<class Arg1, class Arg2, class... FArgs>
		Arg1 Max(Arg1 a, Arg2 b, FArgs... fArgs) { return a < b ? (Arg1)Max(b, fArgs...) : (Arg1)Max(a, fArgs...); }

		template<class Arg>
		Arg Min(Arg a) { return a; }
		template<class Arg1, class Arg2, class... FArgs>
		Arg1 Min(Arg1 a, Arg2 b, FArgs... fArgs) { return a > b ? (Arg1)Min(b, fArgs...) : (Arg1)Min(a, fArgs...); }
		
		inline float Map(float val, float oldMin, float oldMax, float newMin, float newMax) { return newMin + (val - oldMin) / (oldMax - oldMin) * (newMax - newMin); }
		inline double Map(double val, double oldMin, double oldMax, double newMin, double newMax) { return newMin + (val - oldMin) / (oldMax - oldMin) * (newMax - newMin); }
	}
}