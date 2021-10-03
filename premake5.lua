outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
TargetDir = "Bin/" ..outputdir.. "/%{prj.name}"
ObjDir = "Bin/" ..outputdir.. "/Int/%{prj.name}"

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
	includedirs { "$(ProjectDir)Src/", "$(ProjectDir)Vendor/", "$(ProjectDir)Src/OpenGl", "$(ProjectDir)Vendor/GLAD/include", "$(ProjectDir)Vendor/GLFW/include"}
	links { "Opengl32.lib", "GLFW", "GLAD" }

	pchheader "Pch.hpp"
	pchsource "Parrot/Src/Pch.cpp"
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "PT_DEBUG" }
	filter "configurations:Release"
		defines { "PT_LOG_NINFO", "PT_LOG_NEVENT" }
		runtime "Release"
		optimize "on"
	filter "configurations:Dist"
		defines { "PT_NLOG" }
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
	