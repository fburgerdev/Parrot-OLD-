#pragma once
#include "Tracking/Stopwatch.hpp"

namespace Parrot
{
	class Time
	{
	public:
		// Limits the maximum framerate of your application
		// Pass "0" to make the framerate limitless
		static void Framerate(uint32_t frames);
		// Returns the time passed since Parrot started
		static Tracking::Timestep AbsTime();
		// Returns the amount of time the previous update call took
		static Tracking::Timestep DeltaTime();
	};
}