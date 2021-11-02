#pragma once
#include <chrono>

namespace Parrot
{
	namespace Utils
	{
		class Timestep
		{
		public:
			Timestep(float seconds)
				: m_Seconds(seconds) {}
			float Microseconds();
			float Milliseconds();
			float Seconds();
		private:
			float m_Seconds;
		};

		class Stopwatch
		{
		public:
			Stopwatch();

			void Start();
			Timestep Timing();
		private:
			std::chrono::steady_clock::time_point m_StartTime;
		};
	}
}