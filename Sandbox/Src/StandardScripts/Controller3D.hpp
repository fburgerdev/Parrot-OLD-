#pragma once
#include "ParrotScript.hpp"
using namespace Parrot;

class Controller3D : public Component::Script
{
public:
	float speed = 0.3f;
	float mSense = 0.001f;
private:
	Window* wndw;
	Component::Camera* cam;
	bool mouseMovement = true;
public:
	using Script::Script;

	virtual void OnCreate() override
	{
		wndw = &sceneObj.GetScene().GetWindow();
		cam = &sceneObj.GetComponent<Component::Camera>();
		wndw->ShowCursor(false);
	}
	virtual void OnEvent(Event e) override
	{
		if (e.type == EventType::CloseRequest)
			wndw->Close();
		if (e.type == EventType::MousePress && e.mousePress.button == MouseButton::Left && e.mousePress.state == MouseButtonState::Pressed)
		{
			mouseMovement = true;
			wndw->ShowCursor(false);
			wndw->SetCursorPos(wndw->GetSize() / 2);
		}
		if (e.type == EventType::KeyPress && e.keyPress.keyCode == KeyCode::KEY_ESCAPE && e.keyPress.state == KeyState::Pressed)
		{
			if (!mouseMovement)
				wndw->Close();
			else
			{
				mouseMovement = false;
				wndw->ShowCursor(true);
			}
		}
	}
	virtual void OnUpdate() override
	{
		if (!wndw->HasFocus())
			return;
		// camera rotation
		if (mouseMovement)
		{
			Math::Vec2i dMouse = wndw->GetCursorPos() - (Math::Vec2i)((Math::Vec2f)wndw->GetSize() * 0.5f);
			sceneObj.transform.rot.xy += (Math::Vec2f)dMouse * mSense;
			// lock Pitch between -90 to 90 degrees
			if (sceneObj.transform.rot.y > Math::PI_HALFS)
				sceneObj.transform.rot.y = Math::PI_HALFS;
			else if (sceneObj.transform.rot.y < -Math::PI_HALFS)
				sceneObj.transform.rot.y = -Math::PI_HALFS;
			wndw->SetCursorPos(wndw->GetSize() / 2); // center cursor
		}

		// movement
		if (GetKeyState(KeyCode::KEY_W) != KeyState::Released)
			sceneObj.transform.pos += cam->Dir() * speed;
		if (GetKeyState(KeyCode::KEY_S) != KeyState::Released)
			sceneObj.transform.pos -= cam->Dir() * speed;

		if (GetKeyState(KeyCode::KEY_D) != KeyState::Released)
			sceneObj.transform.pos += cam->DirRight() * speed;
		if (GetKeyState(KeyCode::KEY_A) != KeyState::Released)
			sceneObj.transform.pos -= cam->DirRight() * speed;

		if (GetKeyState(KeyCode::KEY_SPACE) != KeyState::Released)
			sceneObj.transform.pos += cam->DirUp() * speed;
		if (GetKeyState(KeyCode::KEY_LEFT_CONTROL) != KeyState::Released)
			sceneObj.transform.pos -= cam->DirUp() * speed;
	}
};
