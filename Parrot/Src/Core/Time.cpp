#include "Ptpch.hpp"
#include "Time.hpp"

namespace Parrot
{
	static Tracking::Stopwatch s_AbsTime;
	static Tracking::Stopwatch s_DeltaTime;
	static Tracking::Timestep s_LastFrameTime(0.0f);
	static float s_MinFrameTime;

	void StartGlobalStopwatch()
	{
		s_AbsTime.Start();
		s_DeltaTime.Start();
	}
	
	void ResolveUpdateStopwatch()
	{
		while (s_DeltaTime.Timing().Seconds() < s_MinFrameTime)
			continue;
		s_LastFrameTime = s_DeltaTime.Timing();
		s_DeltaTime.Start();
	}
	
	void Time::Framerate(uint32_t frames)
	{
		s_MinFrameTime = frames == 0 ? 0.0f : 1.0f / (float)frames;
	}

	Tracking::Timestep Time::AbsTime()
	{
		return s_AbsTime.Timing();
	}
	Tracking::Timestep Time::DeltaTime()
	{
		return s_LastFrameTime;
	}
}