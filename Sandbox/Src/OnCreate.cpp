#include "InternalParrot.hpp"
#include "Controller3D.hpp"
#include "CubeScript.hpp"
#include "ContextManagerScript.hpp"
#include "Math/Arithmetic.hpp"

#include "DefaultMeshCreation.hpp"

void Parrot::Application::Internal_OnCreate()
{
	CreateDefaultMeshes();
	Application::Internal_AddScript("Controller3D", [](SceneObj& obj) { return (Script*)new Controller3D(obj); });
	Application::Internal_AddScript("CubeScript", [](SceneObj& obj) { return (Script*)new CubeScript(obj); });
	Application::Internal_AddScript("ContextManagerScript", [](SceneObj& obj) { return (Script*)new ContextManagerScript(obj); });

	AssetManager::Internal_InitAssetDir(Utils::Directory("..\\TestAssets\\"));
	AssetManager::LoadAsset(Utils::Filename("Main.WNDW"));
	AssetManager::LoadAsset(Utils::Filename("PopUp.WNDW"));
	CreateWindow(AssetManager::GetWindowAsset("Main"));
}