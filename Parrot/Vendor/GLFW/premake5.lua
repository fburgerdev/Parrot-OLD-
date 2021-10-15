project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir (TargetDir)
	objdir (ObjDir)

	systemversion "latest"
	staticruntime "On"

	files
	{
		"Src/win32_init.c",
		"Src/win32_joystick.c",
		"Src/win32_monitor.c",
		"Src/win32_time.c",
		"Src/win32_thread.c",
		"Src/win32_window.c",
		"Src/wgl_context.c",
		"Src/egl_context.c",
		"Src/osmesa_context.c",
		"Include/GLFW/glfw3.h",
		"Include/GLFW/glfw3native.h",
		"Src/glfw_config.h",
		"Src/context.c",
		"Src/init.c",
		"Src/input.c",
		"Src/monitor.c",
		"Src/vulkan.c",
		"Src/window.c"
	}

	defines 
	{ 
		"_GLFW_WIN32",
		"_CRT_SECURE_NO_WARNINGS"
	}
	ignoredefaultlibraries { "LIBCMT" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Optimized"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"