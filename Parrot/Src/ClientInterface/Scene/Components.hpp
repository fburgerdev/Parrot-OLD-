#pragma once
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Assets/Formats/PtMesh.hpp"
#include "Assets/Formats/PtShader.hpp"
#include "Input/Event.hpp"

namespace Parrot
{
	class Transform
	{
	public:
		Transform();
		Transform(const Math::Vec3f& pos, const Math::Vec3f& rot, const Math::Vec3f& scale);

		Math::Mat4f Mat() const;
	public:
		Math::Vec3f pos;
		Math::Vec3f rot;
		Math::Vec3f scale;
	};

	class Renderobject
	{
	public:
		Renderobject(const PtMesh& ptMesh, const PtShader& ptShader);
	public:
		const PtMesh& ptMesh;
		const PtShader& ptShader;
	};

	class Camera
	{
	public:
		Camera(const Transform& transform, float foV, Math::Vec2f zRange = { 0.01f, 1000.0f });

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

	class SceneObject;
	class Script
	{
	public:
		Script(SceneObject& obj);
		virtual ~Script();

		virtual void OnCreate() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event e) {};
	public:
		SceneObject& sceneObject;
	};
	typedef Script* (*ScriptCreationFunc)(SceneObject&);
}