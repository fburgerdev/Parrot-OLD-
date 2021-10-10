Outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
TargetDir = "Bin/" ..Outputdir.. "/%{prj.name}"
ObjDir = "Bin/" ..Outputdir.. "/Int/%{prj.name}"

CppDialect = "C++20"

workspace "Parrot"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Parrot"

include "Parrot/Vendor/GLFW"
include "Parrot/Vendor/GLAD"

project "Parrot"
	location "%{prj.name}"
	kind "Staticlib"
	language "C++"
	staticruntime "off"
	cppdialect(CppDialect)
 	
	targetdir(TargetDir)
	objdir(ObjDir)
	
	files { "%{prj.name}/Src/**.hpp", "%{prj.name}/Src/**.cpp", "%{prj.name}/Src/**.GLSL"}
	includedirs { "$(ProjectDir)Src/","$(ProjectDir)Vendor/", "$(ProjectDir)Vendor/GLAD/Include/", "$(ProjectDir)Vendor/GLFW/Include/"}
	links { "Opengl32.lib", "GLFW", "GLAD" }

	pchheader "Ptpch.hpp"
	pchsource "Parrot/Src/Ptpch.cpp"

	defines { "PT_OPENGL" }
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "PT_DEBUG" }
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	cppdialect(CppDialect)

	targetdir(TargetDir)
	objdir(ObjDir)

	files { "%{prj.name}/Src/**.hpp", "%{prj.name}/Src/**.cpp", "%{prj.name}/Src/**.GLSL"}
	includedirs { "$(ProjectDir)Src/", "Parrot/Src/"}
	links { "Parrot" }

	defines { "PT_OPENGL" }
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "PT_DEBUG" }
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
	