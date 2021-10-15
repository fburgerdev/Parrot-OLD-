#pragma once
#include "Ptpch.hpp"
#include "Math/Vector.hpp"

namespace Parrot
{
	class WindowAPI
	{
	public:
		virtual void Bind() = 0;

		virtual void ShowFrames(bool state) = 0;
		virtual void SetTitle(const std::string& title) = 0;
		virtual const std::string& GetTitle() = 0;

		virtual void SetCursorPos(Math::Vec2i pos) = 0;
		virtual Math::Vec2i GetCursorPos() = 0;

		virtual void Maximize() = 0;
		virtual void Minimize() = 0;

		virtual void SetSize(Math::Vec2u dim) = 0;
		virtual Math::Vec2u GetSize() = 0;

		virtual void Framerate(uint32_t rate) = 0;
		virtual void Update() = 0;
	};

	WindowAPI* CreateWindowAPI(const std::string& name, Math::Vec2u dim);
}