#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class Controller3D : public Script
{
public:
	float speed = 0.1f;
	float mSense = 0.001f;
private:
	Camera& cam;
	Window& window;
public:
	Controller3D(Parrot::SceneObj& obj)
		: Script(obj), cam(sceneObj.GetComponent<Parrot::Camera>()), window(sceneObj.GetScene().GetWindow()){}

	virtual void OnCreate() override
	{
		window.SetCursorPos(window.GetSize() / 2); // center cursor
	}
	virtual void OnEvent(Parrot::Event e) override
	{
		//Log::LogInfo("Input detected");
	}
	virtual void OnUpdate() override
	{
		// camera rotation
		Math::Vec2i dMouse = window.GetCursorPos() - (Math::Vec2i)((Math::Vec2f)window.GetSize() * 0.5f);
		sceneObj.transform.rot.xy += (Math::Vec2f)dMouse * mSense;
		// lock Pitch between -90 to 90 degrees
		if (sceneObj.transform.rot.y > Math::PI_HALFS)
			sceneObj.transform.rot.y = Math::PI_HALFS;
		else if (sceneObj.transform.rot.y < -Math::PI_HALFS)
			sceneObj.transform.rot.y = -Math::PI_HALFS;

		if (GetKeyState(KeyCode::KEY_UP) != KeyState::Released)
			cam.foV += 0.01f;
		else if (GetKeyState(KeyCode::KEY_DOWN) != KeyState::Released)
			cam.foV -= 0.01f;
		
		// roll
		//if (GetKeyState(KeyCode::KEY_LEFT) != KeyState::Released)
		//	sceneObject.transform.rot.z += 0.1f;
		//else if (GetKeyState(KeyCode::KEY_RIGHT) != KeyState::Released)
		//	sceneObject.transform.rot.z -= 0.1f;
		//else
		//	sceneObject.transform.rot.z *= 0.9f;
		//// lock roll between -45 to 45 degrees
		//if (sceneObject.transform.rot.z > Math::PI_QUARTERS)
		//	sceneObject.transform.rot.z = Math::PI_QUARTERS;
		//else if (sceneObject.transform.rot.z < -Math::PI_QUARTERS)
		//	sceneObject.transform.rot.z = -Math::PI_QUARTERS;

		// movement
		if (GetKeyState(KeyCode::KEY_W) != KeyState::Released)
			sceneObj.transform.pos += cam.Dir() * speed;
		if (GetKeyState(KeyCode::KEY_S) != KeyState::Released)
			sceneObj.transform.pos -= cam.Dir() * speed;

		if (GetKeyState(KeyCode::KEY_D) != KeyState::Released)
			sceneObj.transform.pos += cam.DirRight() * speed;
		if (GetKeyState(KeyCode::KEY_A) != KeyState::Released)
			sceneObj.transform.pos -= cam.DirRight() * speed;

		if (GetKeyState(KeyCode::KEY_SPACE) != KeyState::Released)
			sceneObj.transform.pos += cam.DirUp() * speed;
		if (GetKeyState(KeyCode::KEY_LEFT_CONTROL) != KeyState::Released)
			sceneObj.transform.pos -= cam.DirUp() * speed;

		window.SetCursorPos(window.GetSize() / 2); // center cursor
	}
};
