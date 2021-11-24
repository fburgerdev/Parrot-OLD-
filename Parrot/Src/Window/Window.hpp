#pragma once
#include "Assets/Formats/PtWindow.hpp"
#include "Assets/Formats/PtScene.hpp"
#include "Core/PtObj.hpp"

namespace Parrot
{
	class Scene;
	class Window : public PtObj
	{
	public:
		Window(const PtWindow& ptWindow);
		virtual ~Window();

		const std::string& GetTag() const;
		bool IsOpen() const;
		void Close();

		Scene& LoadScene(const PtScene& scene);
		Scene& GetLoadedScene();
		bool IsSceneLoaded();
		void UnloadScene();

		// physical window
		virtual void SetTitle(const std::string& title) = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void SetCursorPos(const Math::Vec2i& pos) = 0;
		virtual Math::Vec2i GetCursorPos() const = 0;

		virtual void Maximize() = 0;
		virtual void Minimize() = 0;

		virtual void SetSize(const Math::Vec2u& dim) = 0;
		virtual Math::Vec2u GetSize() const = 0;
		virtual void Refresh() = 0;

		virtual void GainFocus() = 0;

		virtual void Clear() = 0;
		virtual void Bind() const = 0;
	private:
		std::string m_Tag;
		bool m_IsOpen;
		Scene* m_Scene;
	};
	Window& CreateWindow(const PtWindow& ptWindow);
}