#include "InternalParrot.hpp"
#include "Controller3D.hpp"
#include "DefaultMeshCreation.hpp"

void Parrot::Application::Internal_OnCreate()
{
	//CreateDefaultMeshes();
	Application::Internal_AddScript("Controller3D", [](SceneObj& obj) { return (Component::Script*)new Controller3D(obj); });
	
	AssetManager::Internal_InitAssetDir(Utils::Directory("..\\TestAssets\\"));
	AssetManager::LoadAsset(Utils::Filename("Main.WNDW"));
	AssetManager::LoadAsset(Utils::Filename("PopUp.WNDW"));
	CreateWindow(AssetManager::GetWindowAsset("Main"));
}