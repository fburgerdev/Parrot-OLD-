#include "ParrotSetup.hpp"

#include "StandardScripts/Controller3D.hpp"
#include "ExampleWorld/TerrainGen.hpp"
#include "NoiseTesting.hpp"

namespace Parrot
{
	void OnCreate()
	{
		Internal_AddScriptCreationFunc("Controller3D", [](SceneObj* obj) { return (Component::Script*)new Controller3D(*obj); });
		Internal_AddScriptCreationFunc("TerrainGen", [](SceneObj* obj) { return (Component::Script*)new TerrainGen(*obj); });
		Internal_AddScriptCreationFunc("NoiseTesting", [](SceneObj* obj) { return (Component::Script*)new NoiseTesting(*obj); });
		
		Console::Init(PT_SHOW_CONSOLE);
		DebugOut.Init(&std::cout, nullptr);
		Internal_SetAssetFolder(Utils::Folder(Utils::Directory("Assets/ExampleWorld")));		
		CreateWindow(AssetManager::GetWindowAsset("Main"));
	}
}