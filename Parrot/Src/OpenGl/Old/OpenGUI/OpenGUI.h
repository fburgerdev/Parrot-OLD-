#pragma once
#pragma once
#include "OpenGl.h"
#include <vector>
#include "Slider.h"

class OpenGUI
{
public:
	static void Init(const char* title, Vec2u windowDim, Vec2u screenPos = Vec2u(0));
	static void Terminate();
		   
	static void PushFloat(const std::string& name, float* data, Vec2f boundaries);
	static void PushVec2f(const std::string& name, Vec2f* data, Vec2f boundaries);
	static void PushVec3f(const std::string& name, Vec3f* data, Vec2f boundaries);
	static void PushVec4f(const std::string& name, Vec4f* data, Vec2f boundaries);

	static void Update();
private:
	static void PushName(const std::string& name);
	static void PushOpenGUIFloat(float* data, Vec2f boundaries);
};