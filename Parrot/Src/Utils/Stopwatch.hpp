#pragma once
#include <chrono>

namespace Parrot
{
	namespace Utils
	{
		class Timestep
		{
		public:
			Timestep(float ms);
			float Us();
			float Ms();
			float Sec();
		private:
			float m_Ms;
		};

		class Stopwatch
		{
		public:
			Stopwatch();

			void Reset();
			Timestep Ts();
		private:
			std::chrono::steady_clock::time_point m_ResetTime;
		};
	}
}