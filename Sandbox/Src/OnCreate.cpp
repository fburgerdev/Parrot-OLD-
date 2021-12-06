#include "InternalParrot.hpp"

#include "StandardScripts/Controller3D.hpp"

#include "ExampleWorld/TerrainGen.hpp"

// ExampleWorld
void Parrot::Internal_Application::OnCreate()
{
	Internal_Application::AddScriptCreationFunc("Controller3D", [](SceneObj* obj) { return (Component::Script*)new Controller3D(*obj); });
	Internal_Application::AddScriptCreationFunc("TerrainGen", [](SceneObj* obj) { return (Component::Script*)new TerrainGen(*obj); });

	//Internal_AssetManager::ConvertToAsset(Utils::Filepath("Assets\\ExampleWorld\\Parrot2.jpg"), Utils::Directory("Assets\\ExampleWorld\\"));
	Internal_AssetManager::InitAssetDir(Utils::Directory("Assets\\ExampleWorld\\"));

	AssetManager::LoadWindowAsset(Utils::Filename("Main.WNDW"));
	OpenWindow(AssetManager::GetWindowAsset("Main"));
}