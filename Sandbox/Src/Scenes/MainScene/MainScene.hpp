#pragma once
#include "SceneObjects/Cam.hpp"
#include "SceneObjects/Quad.hpp"

using namespace Parrot;
class MainScene : public Scene
{
public:
	MainScene(const std::string& tag)
		: Scene(tag)
	{
		AddSceneObject(*new Cam("Cam"));
		AddSceneObject(*new Quad("Quad"));
		Log::LogInfo("Cam pos %", GetSceneObject("Cam").transform.position);
	}

	~MainScene()
	{

	}
};