outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
TargetDir = "Bin/" ..outputdir.. "/%{prj.name}"
ObjDir = "Bin/" ..outputdir.. "/Int/%{prj.name}"

CppDialect = "C++20"

workspace "Parrot"
	architecture "x86_64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Parrot"

include "Parrot/Vendor/GLFW"

project "Parrot"
	location "%{prj.name}"
	kind "Staticlib"
	language "C++"
	staticruntime "off"
	cppdialect(CppDialect)
 	
	targetdir(TargetDir)
	objdir(ObjDir)

	files { "%{prj.name}/Src/**"}
	includedirs { "$(ProjectDir)Vendor/GLFW/include" }
	
	links { "Opengl32.lib" }

	links { "GLFW" }
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect(CppDialect)

	targetdir(TargetDir)
	objdir(ObjDir)

	files { "%{prj.name}/Src/**" }
	includedirs { "$(ProjectDir)Src/", "Parrot/Src/"}
	links { "Parrot" }

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
	