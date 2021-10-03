#pragma once
#include <iostream>
#include "Vector.h"

static bool InBounds(uint32_t x, uint32_t min, uint32_t max)
{
	return x <= max && x >= min;
}

template<uint8_t DimIndex, uint8_t OtherIndex>
class Slider
{
public:
	Vec2u slidePos;
	uint32_t slideLength;
	Vec2u sliderDim;
	int32_t sliderProgress;
private:
	bool m_IsTriggered;
	Vec2u m_LastMousePosition;
public:
	Slider()
		: slidePos(0), slideLength(0), sliderDim(0), sliderProgress(0), m_IsTriggered(false) {}
	Slider(Vec2u slidePos, uint32_t slideLength, Vec2u sliderDim, uint32_t sliderProgress = 0)
		: slidePos(slidePos), slideLength(slideLength), sliderDim(sliderDim), sliderProgress(sliderProgress), m_IsTriggered(false) {}

	float GetProgressPercent() { return (float)sliderProgress / (slideLength - sliderDim[DimIndex]); }

	void SetProgressPercent(float percent) 
	{
		if (percent >= 1.0f)
			sliderProgress = slideLength - sliderDim[DimIndex];
		else if (percent <= 0.0f)
			sliderProgress = 0;
		else
			sliderProgress = (uint32_t)((slideLength - sliderDim[DimIndex]) * percent);
	}

	bool IsTriggered(bool isMouseButtonPressed, Vec2u mousePos)
	{
		if (!isMouseButtonPressed)
		{
			m_IsTriggered = false;
			return false;
		}

		if (m_IsTriggered)
		{
			sliderProgress += mousePos[DimIndex] - m_LastMousePosition[DimIndex];
			m_LastMousePosition = mousePos;

			if (sliderProgress < 0)
				sliderProgress = 0;
			else if ((uint32_t)sliderProgress > slideLength - sliderDim[DimIndex])
				sliderProgress = slideLength - sliderDim[DimIndex];
			return true;
		}

		if (isMouseButtonPressed && 
			(mousePos[DimIndex] - slidePos[DimIndex] - sliderProgress >= 0 && mousePos[DimIndex] - slidePos[DimIndex] - sliderProgress <= sliderDim[DimIndex]
			&& mousePos[OtherIndex] - slidePos[OtherIndex] >= 0 && mousePos[OtherIndex] - slidePos[OtherIndex] <= sliderDim[OtherIndex]))
		{
			m_LastMousePosition = mousePos;
			m_IsTriggered = true;
			return true;
		}

		m_IsTriggered = false;
		return false;
	}
};

typedef Slider<0, 1> HorSlider;
typedef Slider<1, 0> VerSlider;
