#pragma once
#include "Parrot.hpp"

class CamControllerPers : public Parrot::Layer
{
public:
	Parrot::SceneObject::PerspectiveCamera m_Cam;
	float m_MoveSpeed;
	float m_MouseSensitivity;

	CamControllerPers(Parrot::Vector::Vec3f pos, Parrot::Vector::Vec3f dir, float foV, Parrot::Vector::Vec2f zRange, float moveSpeed, float mouseSensitivity)
		: m_Cam(pos, dir, foV, zRange), m_MoveSpeed(moveSpeed), m_MouseSensitivity(mouseSensitivity)
	{
	}

	const Parrot::SceneObject::PerspectiveCamera& GetCam() const
	{
		return m_Cam;
	}

	virtual bool ResolveEvent(const Parrot::Event& e) override
	{	
		if (e.type == Parrot::Event::Type::MouseMoveEvent)
		{
			Parrot::Vector::Vec2i mouseOffset = e.mouseMoveEvent.pos - (Parrot::Vector::Vec2i)((Parrot::Vector::Vec2f)Parrot::Window::GetDim() / 2.0f);
			m_Cam.RotateRight((float)mouseOffset.x * m_MouseSensitivity);
			m_Cam.RotateUp(-(float)mouseOffset.y * m_MouseSensitivity);
			Parrot::Input::Mouse::SetPos((Parrot::Vector::Vec2f)Parrot::Window::GetDim() / 2.0f);
			return true;
		}
		return false;
	}
	virtual void OnUpdate() override
	{
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_W) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() + m_Cam.GetDirection() * m_MoveSpeed);
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_S) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() - m_Cam.GetDirection() * m_MoveSpeed);
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_D) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() + m_Cam.GetDirectionRight() * m_MoveSpeed);
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_A) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() - m_Cam.GetDirectionRight() * m_MoveSpeed);
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_SPACE) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() + m_Cam.GetDirectionUp() * m_MoveSpeed);
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_LEFT_CONTROL) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition() - m_Cam.GetDirectionUp() * m_MoveSpeed);
	}
};
