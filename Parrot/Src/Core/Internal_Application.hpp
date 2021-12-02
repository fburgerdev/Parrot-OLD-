#pragma once
#include "Application.hpp"
#include "Scene/Components.hpp"

namespace Parrot
{
	typedef Component::Script* (*ScriptCreationFunc)(SceneObj*);
	namespace Internal_Application
	{
		void OnCreate();

		void AddScriptCreationFunc(const std::string& tag, ScriptCreationFunc func);
		ScriptCreationFunc GetScriptCreationFunc(const std::string& tag);

		void AddWindow(const std::string& tag, Window* window);
		void SetBoundWindow(Window* window);
	}
}