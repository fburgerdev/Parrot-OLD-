-- Directory paths
Outputdir = "Win64-%{cfg.buildcfg}"
TargetDir = "Bin/" ..Outputdir.. "/%{prj.name}"
ObjDir = "Bin/" ..Outputdir.. "/Int/%{prj.name}"

CppDialect = "C++20"

-- Workspace
workspace "Parrot"
	architecture "x64"
	configurations { "Debug", "Optimized", "Dist" }
	startproject "Parrot"

-- Includes
include "Parrot/Vendor/GLFW"
include "Parrot/Vendor/GLAD"

project "Parrot"
	location "%{prj.name}"
	kind "Staticlib"
	language "C++"
	staticruntime "off"

	targetdir(TargetDir)
	objdir(ObjDir)

	cppdialect(CppDialect) 
	
	files { "%{prj.name}/Src/**", "%{prj.name}/Vendor/Stb/*"}
	includedirs { "$(ProjectDir)", "$(ProjectDir)Src/" }
	includedirs { "$(ProjectDir)Vendor/GLAD/Include/", "$(ProjectDir)Vendor/GLFW/Include/" }
	links { "Opengl32.lib", "GLFW", "GLAD" }

	pchheader "Ptpch.hpp"
	pchsource "%{prj.name}/Src/Ptpch.cpp"
	
	ignoredefaultlibraries { "LIBCMT" }
	defines { "PT_OPENGL", "PT_GLFW" }
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "PT_DEBUG" }
	filter "configurations:Optimized"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		defines { "PT_DIST" }

project "Sandbox"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"

	targetdir(TargetDir)
	objdir(ObjDir)

	cppdialect(CppDialect)

	files { "%{prj.name}/Src/**" }
	includedirs { "$(ProjectDir)Src/", "Parrot/Src/"}
	links { "Parrot" }

	ignoredefaultlibraries { "LIBCMT" }
	defines { "PT_OPENGL" }
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines { "PT_DEBUG" }
	filter "configurations:Optimized"
		runtime "Release"
		optimize "on"
		defines { "PT_OPTIMIZED" }
	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		defines { "PT_DIST" }