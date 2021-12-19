#pragma once 
#include "Assets/Formats/WindowAsset.hpp"
#include "Scene/Scene.hpp"

int main();
namespace Parrot
{
	class Window;
	Window& CreateWindow(const Asset::WindowAsset& asset);
	class Window : public PtObj
	{
	protected:
		Window(const Asset::WindowAsset& WindowAsset);
		friend Window& CreateWindow(const Asset::WindowAsset& asset);
	public:
		virtual ~Window();

		bool IsOpen() const;
		void Close();

		Scene& LoadScene(const Asset::SceneAsset& scene);
		Scene& LoadedScene();

		// physical window
		virtual void SetTitle(const std::string& title) = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void SetCursorPos(const Math::Vec2i& pos) = 0;
		virtual Math::Vec2i GetCursorPos() const = 0;

		virtual void ShowCursor(bool state) const = 0;
	
		virtual void Maximized(bool state) = 0;
		virtual void Minimized(bool state) = 0;

		virtual void SetSize(const Math::Vec2u& dim) = 0;
		virtual Math::Vec2u GetSize() const = 0;
		virtual void Resizable(bool state) = 0;

		virtual void SetWindowPos(Math::Vec2i pos) = 0;
		virtual Math::Vec2i GetWindowPos() = 0;

		virtual void GainFocus() = 0;
		virtual bool HasFocus() const = 0;
	protected:
		virtual void Refresh() = 0;
		virtual void Clear() = 0;
		virtual void Bind() const = 0;
	private:
		void UnloadScene();
	private:
		bool m_IsOpen;
		Scene* m_Scene;

		friend int ::main();
	};
}