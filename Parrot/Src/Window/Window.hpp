#pragma once
#include "Ptpch.hpp"
#include "Math/Vector.hpp"
#include "Scene/Scene.hpp"
namespace Parrot
{
	class Window
	{
	private:
		std::string m_Name;
		void* m_WindowAPI;
		bool m_ShouldClose;

		Scene* m_LoadedScene;
	protected:
		virtual void OnCreate() {};
	public:
		Window(const std::string& name, Math::Vec2u dim);
		~Window();

		bool ShouldClose();
		void Close();

		//void LoadScene(const std::string& name);
		//Scene& LoadedScene();

		//Scene& CreateScene(const std::string& name);
		//void DestroyScene(const std::string& name);
		//Scene& GetScene(const std::string& name);
	public:
	// WindowAPI
		void ShowFrames(bool state);
		void SetTitle(const std::string& title);
		const std::string& GetTitle();
		
		void SetCursorPos(Math::Vec2i pos);
		Math::Vec2i GetCursorPos();
		
		void Maximize();
		void Minimize();

		void SetSize(Math::Vec2u dim);
		Math::Vec2u GetSize();
		
		void Framerate(uint32_t rate);
		void Update();
	};
}