#pragma once
#include "Parrot.hpp"

class CamControllerOrtho : public Parrot::Layer
{
public:
	float m_MoveSpeed;
	float m_ScrollSpeed;
	Parrot::SceneObject::OrthographicCamera m_Cam;

	CamControllerOrtho(float moveSpeed, float scrollSpeed)
		: m_MoveSpeed(moveSpeed), m_ScrollSpeed(scrollSpeed)
	{
		m_Cam.SetPosition(0, 0);
		m_Cam.SetWidth((float)Parrot::Window::GetDim().x);
	}

	const Parrot::SceneObject::OrthographicCamera& GetCam() const 
	{
		return m_Cam;
	}

	virtual bool ResolveEvent(const Parrot::Event& e) override
	{
		if (e.type == Parrot::Event::Type::MouseScrollEvent)
		{
			m_Cam.SetWidth(m_Cam.GetDim().x - m_ScrollSpeed * (float)e.mouseScrollEvent.yOffset);
			if (m_Cam.GetDim().x < 20)
				m_Cam.SetWidth(20);
			return true;
		}
		return false;
	}
	virtual void OnUpdate() override 
	{
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_D) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition().xy + Parrot::Vector::Vec2f(m_MoveSpeed, 0));
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_A) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition().xy - Parrot::Vector::Vec2f(m_MoveSpeed, 0));
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_W) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition().xy + Parrot::Vector::Vec2f(0, m_MoveSpeed));
		if (Parrot::Input::Keyboard::GetKeyState(Parrot::Input::Keyboard::Key::KEY_S) != Parrot::Input::Keyboard::KeyState::Released)
			m_Cam.SetPosition(m_Cam.GetPosition().xy - Parrot::Vector::Vec2f(0, m_MoveSpeed));
	}
};
