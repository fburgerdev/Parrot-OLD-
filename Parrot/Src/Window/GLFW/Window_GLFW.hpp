#pragma once
#include "Window/WindowAPI.hpp"
#include "GLFW/glfw3.h"

namespace Parrot
{
	class Window_GLFW : public WindowAPI
	{
	private:
		GLFWwindow* m_Window;
		const char* m_Title;
		bool m_ShowFrames = true;
	public:
		Window_GLFW(const char* title, Math::Vec2u dim, const WindowAPI::Config& config);

		virtual void Maximize() override;
		virtual void ShowFrames(bool state) override;
		virtual void Resize(Math::Vec2u dim) override;
		virtual Math::Vec2u GetSize() override;
		virtual void Display() override;

		virtual void SetCursorPos(Math::Vec2i pos) override;
		virtual Math::Vec2i GetCursorPos() override;
	private:
		void UpdateTitleFrames();
	};
}