#include "InternalParrot.hpp"
#include "Controller3D.hpp"
#include "Prank.hpp"
#include "DefaultMeshCreation.hpp"

void Parrot::Internal_Application::OnCreate()
{
	Internal_Application::AddScriptCreationFunc("Controller3D", [](SceneObj* obj) { return (Component::Script*)new Controller3D(*obj); });
	Internal_Application::AddScriptCreationFunc("Prank", [](SceneObj* obj) { return (Component::Script*)new Prank(*obj); });
	srand((uint32_t)time(0));

	Internal_AssetManager::InitAssetDir(Utils::Directory("..\\TestAssets\\"));
	//AssetManager::Internal_ConvertToAsset(Utils::Filepath("..\\TestAssets\\Lindner\\Lindner.jpg"));
	AssetManager::LoadAsset(Utils::Filename("Main.WNDW"));

	OpenWindow(AssetManager::GetWindowAsset("Main"));
	OpenWindow(AssetManager::GetWindowAsset("Main"));
}