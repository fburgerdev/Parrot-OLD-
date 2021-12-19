#pragma once
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Assets/Formats/MeshAsset.hpp"
#include "Assets/Formats/ShaderAsset.hpp"
#include "Assets/Formats/TexAsset.hpp"
#include "Input/Event.hpp"

namespace Parrot
{
	enum class ComponentType
	{
		None = 0, Transform, RenderObj, Camera, Light
	};
	namespace Asset { class SceneObjAsset; }
	class SceneObj;
	namespace Component
	{
		class Transform
		{
		private:
			Transform();
			Transform(const Math::Vec3f& pos, const Math::Vec3f& rot, const Math::Vec3f& scale);
			friend Asset::SceneObjAsset;
			friend SceneObj;
		public:
			Math::Mat4f Mat() const;
		public:
			Math::Vec3f pos;
			Math::Vec3f rot;
			Math::Vec3f scale;
		};

		class RenderObj
		{
		private:
			RenderObj(const Asset::MeshAsset& mesh, const Asset::TexAsset& tex,  const Asset::ShaderAsset& shader);
			friend Asset::SceneObjAsset;
			friend SceneObj;
		public:
			const Asset::MeshAsset* mesh;
			const Asset::TexAsset* tex;
			const Asset::ShaderAsset* shader;
		};

		class Camera
		{
		private:
			Camera(const Transform& transform, float foV, Math::Vec2f zRange = { 0.01f, 1000.0f });
			Camera(const Transform& transform, const Camera& other);
			friend Asset::SceneObjAsset;
			friend SceneObj;
		public:
			Math::Vec3f Dir() const;
			Math::Vec3f DirUp() const;
			Math::Vec3f DirRight() const;

			Math::Mat4f ViewProjMat() const;
		public:
			float foV;
			Math::Vec2f zRange;
		private:
			const Transform& m_Transform;
		};

		class Script
		{
		public:
			Script(SceneObj& obj);
			friend Asset::SceneObjAsset;
			friend SceneObj;
		public:
			virtual ~Script();

			virtual void OnCreate() {};
			virtual void OnUpdate() {};
			virtual void OnEvent(Event e) {};
		public:
			SceneObj& sceneObj;
		};

		class Light
		{
		private:
			Light(Math::Vec3f dir = { 0, -1, 0 }, Math::Vec3u8 color = { 255, 255, 255 }, float intensity = 1.0f);
			friend Asset::SceneObjAsset;
			friend SceneObj;
		public:
			Math::Vec3f dir;
			Math::Vec3u8 color;
			float intensity;
		};
	}
}