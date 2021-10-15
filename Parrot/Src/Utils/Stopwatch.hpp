#pragma once
#include "Ptpch.hpp"

namespace Parrot
{
	namespace Utils
	{
		class Timestep
		{
		private:
			float m_Seconds;
		public:
			Timestep(float seconds)
				: m_Seconds(seconds) {}
			float Microseconds();
			float Milliseconds();
			float Seconds();
		};

		class Stopwatch
		{
		private:
			std::chrono::steady_clock::time_point m_StartTime;
		public:
			Stopwatch();

			void Start();
			Timestep Timing();
		};
	}
}