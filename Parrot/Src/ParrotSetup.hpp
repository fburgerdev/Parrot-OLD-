#pragma once
#include "ParrotScript.hpp"

#include "Debug/Console.hpp"
#include "Assets/DefaultAssets.hpp"

namespace Parrot
{
	void Internal_SetAssetFolder(const Utils::Folder& folder);
	void Internal_AddScriptCreationFunc(const std::string& tag, ScriptCreationFunc func);
}