#pragma once
#include <memory>

namespace Parrot
{
	class PtObj
	{
	public:
		enum class Type : int8_t
		{
			Unknown = -1, Window, Scene, SceneObj, WindowAsset, SceneAsset, SceneObjAsset, MeshAsset, TexAsset, ShaderAsset, Script, Light
		};
		uint64_t ID() const;
	protected:
		PtObj(Type type);
		~PtObj();
	private:
		uint64_t m_ID;
		Type m_Type;
		static uint64_t s_IDCount;
		static uint64_t s_ObjCount[9];
	};
}