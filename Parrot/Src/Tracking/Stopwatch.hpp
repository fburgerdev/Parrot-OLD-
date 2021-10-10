#pragma once
#include "Ptpch.hpp"

namespace Parrot
{
	namespace Tracking
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

			// Resets stopwatch
			void Start();
			// Returns time passed since the last Start() call
			// If Start() was never called, it returns the time passed since the Stopwatch was instantiated
			Timestep Timing();
		};
	}
}