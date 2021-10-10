#include "Ptpch.hpp"
#include "Stopwatch.hpp"

namespace Parrot
{
	namespace Tracking
	{
		float Timestep::Microseconds()
		{
			return m_Seconds * 1000000;
		}

		float Timestep::Milliseconds()
		{
			return m_Seconds * 1000;
		}

		float Timestep::Seconds()
		{
			return m_Seconds;
		}

		Stopwatch::Stopwatch()
		{
			Start();
		}

		void Stopwatch::Start()
		{
			m_StartTime = std::chrono::high_resolution_clock::now();
		}

		Timestep Stopwatch::Timing()
		{
			auto duration = std::chrono::high_resolution_clock::now() - m_StartTime;
			return Timestep((float)std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000000.0f);
		}
	}
}