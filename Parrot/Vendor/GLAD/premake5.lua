project "GLAD"
	kind "StaticLib"
	language "C"

	targetdir (TargetDir)
	objdir (ObjDir)

	systemversion "latest"
	staticruntime "On"

	files
	{
		"include/GLAD/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
	
	
	includedirs 
	{
		"Include"
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