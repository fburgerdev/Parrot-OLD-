#pragma once
#include "Parrot.hpp"

using namespace Parrot;
class Cam : public SceneObject
{
public:
	Cam(const std::string& tag)
		: SceneObject(tag)
	{
		transform.position.x = 2;
	}

	~Cam()
	{

	}
};