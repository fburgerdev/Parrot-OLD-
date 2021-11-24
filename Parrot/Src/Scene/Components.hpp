#pragma once
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Assets/Formats/PtMesh.hpp"
#include "Assets/Formats/PtShader.hpp"
#include "Assets/Formats/PtTex.hpp"
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

	class Renderobj
	{
	public:
		Renderobj(const PtMesh& ptMesh, const PtShader& ptShader, const PtTex& ptTex);
		Renderobj(const Renderobj& other);
	public:
		const PtMesh& ptMesh;
		const PtShader& ptShader;
		const PtTex& ptTex;
	};

	class Camera
	{
	public:
		Camera(const Transform& transform, float foV, Math::Vec2f zRange = { 0.01f, 1000.0f });
		Camera(const Transform& transform, const Camera& other);

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

	class SceneObj;
	class Script
	{
	public:
		Script(SceneObj& obj);
		virtual ~Script();

		virtual void OnCreate() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event e) {};
	public:
		SceneObj& sceneObj;
	};
	typedef Script* (*ScriptCreationFunc)(SceneObj&);
}