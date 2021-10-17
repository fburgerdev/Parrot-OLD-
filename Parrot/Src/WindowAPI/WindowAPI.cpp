#include "Ptpch.hpp"
#include "WindowAPI.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	WindowAPI* CreateWindowAPI(const std::string& title, Math::Vec2u size, Window* window)
	{
		#ifdef PT_GLFW
			return new Window_GLFW(title, size, window);
		#else
			#error No WindowAPI specified! Options: "PT_GLFW"
		#endif
	}
}