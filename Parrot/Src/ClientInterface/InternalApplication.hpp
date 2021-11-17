#pragma once
#include "Application.hpp"
#include "ClientInterface/Scene/Components.hpp"

namespace Parrot
{
	namespace Application
	{
		extern void OnCreate();

		void AddScript(const std::string& tag, ScriptCreationFunc func);
		ScriptCreationFunc GetScript(const std::string& tag);

		void AddWindow(const std::string& tag, Window* window);
		void RemoveWindow(const std::string& tag);
	}
}