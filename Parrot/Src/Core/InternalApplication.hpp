#pragma once
#include "Application.hpp"
#include "Scene/Components.hpp"

namespace Parrot
{
	namespace Application
	{
		extern void Internal_OnCreate();

		void Internal_AddScript(const std::string& tag, ScriptCreationFunc func);
		ScriptCreationFunc Internal_GetScript(const std::string& tag);

		void Internal_AddWindow(const std::string& tag, Window* window);
		void Internal_RemoveWindow(const std::string& tag);
		void Internal_SetBoundWindow(Window* window);
	}
}