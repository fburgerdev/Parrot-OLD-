#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class ContextManagerScript : public Script
{
public:
	ContextManagerScript(Parrot::SceneObj& obj)
		: Script(obj) {}

	virtual void OnCreate() override
	{
		
	}
	virtual void OnEvent(Event e) override
	{
		if (e.type == EventType::CloseRequest || (e.type == EventType::KeyPress && e.keyPress.keyCode == KeyCode::KEY_ESCAPE))
			sceneObj.GetScene().GetWindow().Close();
	}
	virtual void OnUpdate() override
	{

	}
};

