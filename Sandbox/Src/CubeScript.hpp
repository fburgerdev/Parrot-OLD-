#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class CubeScript : public Script
{
public:
	float speed = 0.0f;
	Transform* camT = nullptr;
public:
	CubeScript(Parrot::SceneObj& obj)
		: Script(obj) {}

	virtual void OnCreate() override
	{
		camT = &sceneObj.GetScene().GetSceneObj("Camera").transform;
	}
	virtual void OnEvent(Event e) override
	{
		
	}
	virtual void OnUpdate() override
	{
		Log::LogInfo("%", GetPtObjNumber(AssetManager::GetShaderAsset("Default").GetObjID()));
		//sceneObject.transform.rot += Math::Vec3f(0.04f, 0.001f, 0.001f);
		if (sceneObj.transform.pos.y <= 0.0f)
		{
			speed *= -1;
			sceneObj.GetScene().RaiseEvent(Event(EventType::Custom, 1));
		}
		else
			speed -= 0.01f;
		sceneObj.transform.pos.y += speed;
	}
};
