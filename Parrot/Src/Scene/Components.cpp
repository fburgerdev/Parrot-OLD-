#include "Ptpch.hpp"
#include "Components.hpp"
#include "Window/Window.hpp"
#include "SceneObj.hpp"

#include <cmath>

namespace Parrot
{
	Window& Internal_GetBoundWindow();
	namespace Component
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

			float sina = sin(rot.z);
			float cosa = cos(rot.z);
			float sinb = sin(rot.x);
			float cosb = cos(rot.x);
			float sinc = sin(rot.y);
			float cosc = cos(rot.y);
			out[0][0] = cosa * cosb * scale.x;
			out[0][1] = sina * cosb * scale.x;
			out[0][2] = -sinb * scale.x;
			out[1][0] = (cosa * sinb * sinc - sina * cosc) * scale.y;
			out[1][1] = (sina * sinb * sinc + cosa * cosc) * scale.y;
			out[1][2] = cosb * sinc * scale.y;
			out[2][0] = (cosa * sinb * cosc + sina * sinc) * scale.z;
			out[2][1] = (sina * sinb * cosc - cosa * sinc) * scale.z;
			out[2][2] = cosb * cosc * scale.z;
			out[3][3] = 1;
			memcpy(out[3], &pos, sizeof(float) * 3);
			return out;
		}

		RenderObj::RenderObj(const Asset::MeshAsset& mesh, const Asset::TexAsset& tex, const Asset::ShaderAsset& shader)
			: mesh(&mesh), tex(&tex), shader(&shader)
		{

		}

		Camera::Camera(const Transform& transform, float foV, Math::Vec2f zRange)
			: m_Transform(transform), foV(foV), zRange(zRange)
		{

		}
		Camera::Camera(const Transform& transform, const Camera& other)
			: m_Transform(transform), foV(other.foV), zRange(other.zRange)
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
			Math::Vec2u winSize = Internal_GetBoundWindow().GetSize();
			proj[1][1] = winSize.x / (float)winSize.y * tanFoV;
			proj[2][2] = zRange.b / (zRange.b - zRange.a);
			proj[3][2] = zRange.a * zRange.b / (zRange.a - zRange.b);
			proj[2][3] = 1;

			return proj * view;
		}

		Script::Script(SceneObj& obj)
			: sceneObj(obj)
		{

		}
		Script::~Script()
		{

		}
		
		Light::Light(Math::Vec3f dir, Math::Vec3u8 color, float intensity)
			: dir(dir), color(color), intensity(intensity)
		{

		}
	}
}