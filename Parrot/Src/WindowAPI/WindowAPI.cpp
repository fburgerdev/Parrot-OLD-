#include "Ptpch.hpp"
#include "WindowAPI.hpp"
#include "GLFW/Window_GLFW.hpp"

namespace Parrot
{
	WindowAPI* CreateWindowAPI(const std::string& title, const Math::Vec2u& dim)
	{
		#ifdef PT_GLFW
			return new Window_GLFW(title, dim);
		#else
			#error No WindowAPI specified! Options: "PT_GLFW"
		#endif
	}
}