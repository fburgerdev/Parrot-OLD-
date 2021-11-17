#pragma once
#include "Scene/Scene.hpp"
#include "Assets/Formats/PtWindow.hpp"
#include "WindowAPI/WindowAPI.hpp"

namespace Parrot
{
	class Window
	{
	public:
		Window(const PtWindow& ptWindow);
		~Window();

		const std::string& GetTag() const;
		bool ShouldClose() const;
		void Close();

		Scene& LoadScene(const PtScene& scene);
		Scene& GetLoadedScene();
		bool IsSceneLoaded();
		void UnloadScene();

		WindowAPI& GetWindowAPI();
	private:
		std::string m_Tag;
		WindowAPI* m_WindowAPI;
		Scene* m_Scene;
		bool m_ShouldClose;
	};
}