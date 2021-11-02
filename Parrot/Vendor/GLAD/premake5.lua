project "GLAD"
	kind "StaticLib"
	language "C"

	targetdir (TargetDir)
	objdir (ObjDir)

	systemversion "latest"
	staticruntime "On"

	files
	{
		"Include/GLAD/glad.h",
		"Include/KHR/khrplatform.h",
		"Src/glad.c"
	}
	
	includedirs 
	{
		"Include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Optimized"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"