#include "Ptpch.hpp"
#include "Stopwatch.hpp"

namespace Parrot
{
	namespace Utils
	{
		Timestep::Timestep(float ms)
			: m_Ms(ms) {}
		float Timestep::Us()
		{
			return m_Ms * 1000.0f;
		}
		float Timestep::Ms()
		{
			return m_Ms;
		}
		float Timestep::Sec()
		{
			return m_Ms / 1000.0f;
		}

		Stopwatch::Stopwatch()
		{
			Reset();
		}
		void Stopwatch::Reset()
		{
			m_ResetTime = std::chrono::high_resolution_clock::now();
		}

		Timestep Stopwatch::Ts()
		{
			auto duration = std::chrono::high_resolution_clock::now() - m_ResetTime;
			return Timestep((float)std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1000.0f);
		}
	}
}