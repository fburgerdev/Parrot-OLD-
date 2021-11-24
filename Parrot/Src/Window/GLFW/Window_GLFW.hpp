#pragma once
#include "Window/Window.hpp"
#include "GLFW/glfw3.h"

namespace Parrot
{
	class Window_GLFW : public Window
	{
	public:
		Window_GLFW(const PtWindow& ptWindow);
		~Window_GLFW();

		virtual void SetTitle(const std::string& title) override;
		virtual const std::string& GetTitle() const override;

		virtual void SetCursorPos(const Math::Vec2i& pos) override;
		virtual Math::Vec2i GetCursorPos() const override;

		virtual void Maximize() override;
		virtual void Minimize() override;

		virtual void SetSize(const Math::Vec2u& dim) override;
		virtual Math::Vec2u GetSize() const override;

		virtual void Refresh() override;

		virtual void GainFocus() override;

		virtual void Clear() override;
		virtual void Bind() const override;
	private:
		GLFWwindow* m_Window;
		std::string m_Title;
		//bool m_IsFocused;
	};
}