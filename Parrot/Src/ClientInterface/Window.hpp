#pragma once
#include <string>
#include "Math/Vector.hpp"
#include "Input/Event.hpp"
#include "Scene/Scene.hpp"

namespace Parrot
{
	class Window
	{
	public:
		// potential client override
		virtual void OnEvent(Event e) {};

		Window(const std::string& tag, Math::Vec2u size);
		virtual ~Window();

		const std::string& GetTag() const { return m_Tag; }
		bool ShouldClose() const;
		void Close();

		Scene& LoadScene(const std::string& tag);
		void LoadScene(Scene& scene);
		void UnloadScene();

		// WindowAPI
		void SetTitle(const std::string& title);
		const std::string& GetTitle() const;
		
		void SetCursorPos(Math::Vec2i pos);
		Math::Vec2i GetCursorPos() const;
		
		void Maximize();
		void Minimize();

		void SetSize(Math::Vec2u dim);
		Math::Vec2u GetSize() const;
		
		void Update();
	private:
		std::string m_Tag;
		void* m_WindowAPI;
		Scene* m_LoadedScene;
		bool m_ShouldClose;
	};
}