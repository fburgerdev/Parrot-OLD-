#pragma once
#include "Window/WindowAPI.hpp"
#include "GLFW/glfw3.h"
#include "Utils/Stopwatch.hpp"

namespace Parrot
{
	class Window_GLFW : public WindowAPI
	{
	private:
		GLFWwindow* m_Window;
		std::string m_Title;

		Math::Vec2i m_CursorPos;
		Math::Vec2u m_WindowDim;

		uint32_t m_Framerate;
		bool m_ShowFrames = true;
		Utils::Stopwatch m_FrameWatch;
	public:
		Window_GLFW(const std::string& name, Math::Vec2u dim);
		~Window_GLFW();

		virtual void Bind() override;

		virtual void ShowFrames(bool state) override;
		virtual void SetTitle(const std::string& title) override;
		virtual const std::string& GetTitle() override;

		virtual void SetCursorPos(Math::Vec2i pos) override;
		virtual Math::Vec2i GetCursorPos() override;

		virtual void Maximize() override;
		virtual void Minimize() override;

		virtual void SetSize(Math::Vec2u dim) override;
		virtual Math::Vec2u GetSize() override;

		virtual void Framerate(uint32_t framerate) override;
		virtual void Update() override;

	private:
		void UpdateTitleFrames();
	};
}