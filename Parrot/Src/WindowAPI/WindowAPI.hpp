#pragma once
#include "Ptpch.hpp"
#include "Math/Vector.hpp"
#include "ClientInterface/Window.hpp"

namespace Parrot
{
	class WindowAPI
	{
	public:
		virtual ~WindowAPI() {};

		virtual void Bind() const = 0;

		virtual void SetTitle(const std::string& title) = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void SetCursorPos(Math::Vec2i pos) = 0;
		virtual Math::Vec2i GetCursorPos() const = 0;

		virtual void Maximize() = 0;
		virtual void Minimize() = 0;

		virtual void SetSize(Math::Vec2u dim) = 0;
		virtual Math::Vec2u GetSize() const= 0;
		virtual void Update() = 0;
	};

	WindowAPI* CreateWindowAPI(const std::string& title, Math::Vec2u size, Window* window);
}