#pragma once
#include <memory>

namespace Parrot
{
	class DebugMsg
	{
	public:
		enum class Type: uint8_t
		{
			Info, Warning, Error
		};
	public:
		DebugMsg(Type type, const char* name, const char* explanation);
	public:
		uint64_t code;
		Type type;
		const char* name;
		const char* explanation;
	};

	extern const DebugMsg FileContextWarning;
	extern const DebugMsg UnknownExtWarning;
	extern const DebugMsg SceneObjLookupWarning;
	extern const DebugMsg AssetSyntaxWarning;
	extern const DebugMsg ImageLoadWarning;
	extern const DebugMsg AssetManagerLookupError;
	extern const DebugMsg GLFWInitError;
	extern const DebugMsg WindowCreationError;
	extern const DebugMsg GLEWInitError;
	extern const DebugMsg WindowLookupWarning;
	extern const DebugMsg ComponentLookupWarning;
	extern const DebugMsg UnknownDirWarning;
}