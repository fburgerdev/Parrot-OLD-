#pragma once
#include "Math/Vector.hpp"
#include "Input/Event.hpp"

namespace Parrot
{
	class WindowAPI
	{
	public:
		virtual ~WindowAPI() {};

		virtual void Bind() const = 0;

		virtual void SetTitle(const std::string& title) = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void SetCursorPos(const Math::Vec2i& pos) = 0;
		virtual Math::Vec2i GetCursorPos() const = 0;

		virtual void Maximize() = 0;
		virtual void Minimize() = 0;

		virtual void SetSize(const Math::Vec2u& dim) = 0;
		virtual Math::Vec2u GetSize() const= 0;
		virtual void Update() = 0;

		virtual void Clear() = 0;

		virtual bool PollEvent(Event& e) = 0;
	};

	WindowAPI* CreateWindowAPI(const std::string& title, const Math::Vec2u& dim);
}