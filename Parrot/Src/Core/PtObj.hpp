#pragma once
#include <memory>

namespace Parrot
{
	enum class PtObjType : int8_t
	{
		Unknown = -1, Window, Scene, SceneObj, PtWindow, PtScene, PtSceneObj, PtMesh, PtTex, PtShader
	};
	constexpr PtObjType DeducePtObjType(uint64_t objID)
	{
		int32_t i = 0;
		while (!(objID & ((uint64_t)1 << (62 - i))))
			i++;
		if (i > 8)
			return PtObjType::Unknown;
		return (PtObjType)i;
	}
	constexpr int32_t GetPtObjNumber(uint64_t objID)
	{
		return (int32_t)(objID & ((uint64_t)0xFFFFFFFF));
	}

	class PtObj
	{
	public:
		PtObj(PtObjType type);
		uint64_t GetObjID() const;
	private:
		uint64_t m_ID;
		static uint64_t s_ObjCount[9];
	};
}