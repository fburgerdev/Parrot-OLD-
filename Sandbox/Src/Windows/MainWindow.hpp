#pragma once
#include "Scenes/MainScene/MainScene.hpp"

class MainWindow: public Parrot::Window
{
public:
	MainWindow(const std::string& tag, Math::Vec2u size)
		: Window(tag, size)
	{
		LoadScene(*new MainScene("Scene 1"));
	}

	virtual void OnEvent(Event e) override
	{
		if (e.type == Event::Type::WindowCloseRequestEvent)
			Close();
		//Log::LogInfo("OnEvent");
	}

	~MainWindow()
	{

	}
};
