#include "Ptpch.hpp"
#include "Window.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	WindowAPI* CreateWindowAPI(const std::string& name, Math::Vec2u dim)
	{
		#ifdef PT_GLFW
			return new Window_GLFW(name, dim);
		#else
			#error No WindowAPI specified! Options: "PT_GLFW"
		#endif
	}
}