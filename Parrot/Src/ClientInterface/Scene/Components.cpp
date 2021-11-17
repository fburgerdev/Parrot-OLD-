#include "Ptpch.hpp"
#include "Components.hpp"
#include "Debug/InternalLog.hpp"
#include <cmath>

namespace Parrot
{
	Transform::Transform()
		: pos(0), rot(0), scale(1)
	{

	}
	Transform::Transform(const Math::Vec3f& pos, const Math::Vec3f& rot, const Math::Vec3f& scale)
		: pos(pos), rot(rot), scale(scale)
	{
	
	}
	Math::Mat4f Transform::Mat() const
	{ 
		Math::Mat4f out;
		out.Identity();
		out = Math::Translate(out, pos) * Math::RotationMat(rot);
		Math::Scale(out, scale);
		return out;
	}

	Renderobject::Renderobject(const PtMesh& ptMesh, const PtShader& ptShader)
		: ptMesh(ptMesh), ptShader(ptShader)
	{

	}

	Camera::Camera(const Transform& transform, float foV, Math::Vec2f zRange)
		: m_Transform(transform), foV(foV), zRange(zRange)
	{

	}
	Math::Vec3f Camera::Dir() const
	{
		return (Math::RotationMat(m_Transform.rot) * Math::Vec4f(0, 0, 1, 0)).xyz;
	}
	Math::Vec3f Camera::DirUp() const
	{
		return (Math::RotationMat(m_Transform.rot) * Math::Vec4f(0, 1, 0, 0)).xyz;
	}
	Math::Vec3f Camera::DirRight() const
	{
		return (Math::RotationMat(m_Transform.rot) * Math::Vec4f(1, 0, 0, 0)).xyz;
	}

	Math::Mat4f Camera::ViewProjMat() const
	{
		Math::Mat4f rotMat = Math::RotationMat(m_Transform.rot);
		Math::Vec4f n = rotMat * Math::Vec4f(0, 0, 1, 0);
		Math::Vec4f nRight = rotMat * Math::Vec4f(1, 0, 0, 0);
		Math::Vec4f nUp = rotMat * Math::Vec4f(0, 1, 0, 0);

		Math::Mat4f view;
		view[0][0] = nRight.x;
		view[0][1] = nUp.x;
		view[0][2] = n.x;

		view[1][0] = nRight.y;
		view[1][1] = nUp.y;
		view[1][2] = n.y;
		
		view[2][0] = nRight.z;
		view[2][1] = nUp.z;
		view[2][2] = n.z;
		
		view[3][3] = 1;
		
		Math::Translate(view, (view * Math::Vec4f(-m_Transform.pos, 0)).xyz);
		Math::Mat4f proj;
		float tanFoV = 1.0f / tanf(foV / 2);
		proj[0][0] = tanFoV;
		proj[1][1] = (1080.0f / 720.0f) * tanFoV;
		proj[2][2] = zRange.b / (zRange.b - zRange.a);
		proj[3][2] = zRange.a * zRange.b / (zRange.a - zRange.b);
		proj[2][3] = 1;

		return proj * view;
	}

	Script::Script(SceneObject& obj)
		: sceneObject(obj)
	{

	}
	Script::~Script()
	{

	}

}