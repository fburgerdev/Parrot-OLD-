#include "Ptpch.hpp"
#include "DebugMsg.hpp"

namespace Parrot
{
	const DebugMsg FileContextWarning(DebugMsg::Type::Warning, "FileContextWarning", "Failed to open file. Check whether the file is used by another process or is corrupted.");
	const DebugMsg UnknownExtWarning(DebugMsg::Type::Warning, "UnknownExtWarning", "Filename has no valid Extension.");
	const DebugMsg SceneObjLookupWarning(DebugMsg::Type::Warning, "SceneObjLookupWarning", "Could not find SceneObj in Scene. Check if the tag was misspelled.");
	const DebugMsg AssetSyntaxWarning(DebugMsg::Type::Warning, "AssetSyntaxWarning", "Syntax error occured in asset file.");
	const DebugMsg ImageLoadWarning(DebugMsg::Type::Warning, "ImageLoadWarning", "Image couldn't be loaded. Check whether the image is used by another process or is corrupted. Note that Parrot currently only supports .png and .jpg images.");
	const DebugMsg AssetManagerLookupError(DebugMsg::Type::Error, "AssetManagerLookupError", "Asset couldn't be found in asset folder.");
	const DebugMsg GLFWInitError(DebugMsg::Type::Error, "GLFWInitError", "GLFW initialization failed.");
	const DebugMsg WindowCreationError(DebugMsg::Type::Error, "WindowCreationError", "GLFW initialization failed.");
	const DebugMsg GLEWInitError(DebugMsg::Type::Error, "GLEWInitError", "GLFW initialization failed.");
	const DebugMsg WindowLookupWarning(DebugMsg::Type::Warning, "WindowLookupWarning", "GLFW initialization failed.");
	const DebugMsg ComponentLookupWarning(DebugMsg::Type::Warning, "ComponentLookupWarning", "GLFW initialization failed.");
	const DebugMsg UnknownDirWarning(DebugMsg::Type::Warning, "UnknownDirWarning", "Directory couldn't be found.");

	static uint64_t s_MsgCount = 0;
	DebugMsg::DebugMsg(Type type, const char* name, const char* explanation)
		: code(++s_MsgCount), type(type), name(name), explanation(explanation) 
	{

	}
}