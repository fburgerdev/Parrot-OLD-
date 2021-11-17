#include "ParrotScript.hpp"
using namespace Parrot;

class Controller3D : public Script
{
public:
	float speed = 0.1f;
	float mSense = 0.001f;
private:
	Camera& cam;
	WindowAPI& wAPI;
public:
	Controller3D(Parrot::SceneObject& obj)
		: Script(obj), cam(sceneObject.GetComponent<Parrot::Camera>()), wAPI(Application::MainWindow().GetWindowAPI()) {}

	virtual void OnCreate() override
	{
		wAPI.SetCursorPos(wAPI.GetSize() / 2); // center cursor
	}
	virtual void OnEvent(Parrot::Event e) override
	{
		if (e.type == Event::Type::KeyboardEvent)
			if (e.keyboardEvent.keyCode == KeyCode::KEY_ESCAPE && e.keyboardEvent.state == KeyState::Pressed)
				sceneObject.GetScene().GetWindow().Close();
	}
	virtual void OnUpdate() override
	{
		// camera rotation
		Math::Vec2i dMouse = wAPI.GetCursorPos() - (Math::Vec2i)((Math::Vec2f)wAPI.GetSize() * 0.5f);
		sceneObject.transform.rot.xy += (Math::Vec2f)dMouse * mSense;
		// lock Pitch between -90 to 90 degrees
		if (sceneObject.transform.rot.y > Math::PI_HALFS)
			sceneObject.transform.rot.y = Math::PI_HALFS;
		else if (sceneObject.transform.rot.y < -Math::PI_HALFS)
			sceneObject.transform.rot.y = -Math::PI_HALFS;

		if (GetKeyState(KeyCode::KEY_UP) != KeyState::Released)
			cam.foV += 0.01f;
		else if (GetKeyState(KeyCode::KEY_DOWN) != KeyState::Released)
			cam.foV -= 0.01f;

		// roll
		if (GetKeyState(KeyCode::KEY_LEFT) != KeyState::Released)
			sceneObject.transform.rot.z += 0.1f;
		else if (GetKeyState(KeyCode::KEY_RIGHT) != KeyState::Released)
			sceneObject.transform.rot.z -= 0.1f;
		else
			sceneObject.transform.rot.z *= 0.9f;
		// lock roll between -45 to 45 degrees
		if (sceneObject.transform.rot.z > Math::PI_QUARTERS)
			sceneObject.transform.rot.z = Math::PI_QUARTERS;
		else if (sceneObject.transform.rot.z < -Math::PI_QUARTERS)
			sceneObject.transform.rot.z = -Math::PI_QUARTERS;

		// movement
		if (GetKeyState(KeyCode::KEY_W) != KeyState::Released)
			sceneObject.transform.pos += cam.Dir() * speed;
		if (GetKeyState(KeyCode::KEY_S) != KeyState::Released)
			sceneObject.transform.pos -= cam.Dir() * speed;

		if (GetKeyState(KeyCode::KEY_D) != KeyState::Released)
			sceneObject.transform.pos += cam.DirRight() * speed;
		if (GetKeyState(KeyCode::KEY_A) != KeyState::Released)
			sceneObject.transform.pos -= cam.DirRight() * speed;

		if (GetKeyState(KeyCode::KEY_SPACE) != KeyState::Released)
			sceneObject.transform.pos += cam.DirUp() * speed;
		if (GetKeyState(KeyCode::KEY_LEFT_CONTROL) != KeyState::Released)
			sceneObject.transform.pos -= cam.DirUp() * speed;

		wAPI.SetCursorPos(wAPI.GetSize() / 2); // center cursor
	}
	
	static Script* Create(SceneObject& obj)
	{
		return new Controller3D(obj);
	}
};
