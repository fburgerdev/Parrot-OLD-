#include "InternalParrot.hpp"
#include "Controller3D.hpp"

void Parrot::Application::OnCreate()
{
	Application::AddScript("Controller3D", [](SceneObject& obj) { return (Script*)new Controller3D(obj); });

	AssetManager::InitAssetDir(Utils::Directory("..\\TestAssets\\"));
	AssetManager::LoadAsset(Utils::Filename("MainWindow.WNDW"));
	new Window(AssetManager::GetWindowAsset("MainWindow"));
}