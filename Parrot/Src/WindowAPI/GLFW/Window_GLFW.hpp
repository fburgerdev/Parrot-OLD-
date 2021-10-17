#pragma once
#include "WindowAPI/WindowAPI.hpp"
#include "GLFW/glfw3.h"

namespace Parrot
{
	class Window_GLFW : public WindowAPI
	{
	public:
		Window_GLFW(const std::string& title, Math::Vec2u dim, Window* window);
		~Window_GLFW();

		virtual void Bind() const override;

		virtual void SetTitle(const std::string& title) override;
		virtual const std::string& GetTitle() const override;

		virtual void SetCursorPos(Math::Vec2i pos) override;
		virtual Math::Vec2i GetCursorPos() const override;

		virtual void Maximize() override;
		virtual void Minimize() override;

		virtual void SetSize(Math::Vec2u dim) override;
		virtual Math::Vec2u GetSize() const override;

		virtual void Update() override;
	private:
		GLFWwindow* m_Window;
		std::stack<Event> m_Events;
		std::string m_Title;

		Math::Vec2i m_CursorPos;
		Math::Vec2u m_WindowDim;
		bool m_ShowFrames = true;
	};
}