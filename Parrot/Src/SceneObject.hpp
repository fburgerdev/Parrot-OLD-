#pragma once
#include "Vector.hpp"
#include "OpenGl/Texture.hpp"
#include "Window.hpp"

namespace Parrot
{
	namespace SceneObject
	{
		class OrthographicCamera
		{
		private:
			Vector::Vec3f m_Pos;
			bool m_SizeByWidth;
			float m_Size;
		public:
			OrthographicCamera(Vector::Vec3f pos, float width)
				: m_Pos(pos), m_SizeByWidth(true), m_Size(width) {}
			OrthographicCamera()
				: m_Pos(0), m_SizeByWidth(true), m_Size(0) {}

			Vector::Vec3f GetPosition() const { return m_Pos; }

			void SetPosition(Vector::Vec3f pos) { m_Pos = pos; }
			void SetPosition(float x, float y, float z) { m_Pos = Vector::Vec3f(x, y, z); }
			void SetPosition(Vector::Vec2f pos) { m_Pos = Vector::Vec3f(pos, 0); }
			void SetPosition(float x, float y) { m_Pos = Vector::Vec3f(x, y, 0); }

			void SetWidth(float width) { m_SizeByWidth = true; m_Size = width; }
			void SetHeight(float height) { m_SizeByWidth = false; m_Size = height; }
			Vector::Vec2f GetDim() const
			{
				if (m_SizeByWidth)
					return Vector::Vec2f(m_Size, (float)Window::GetDim().y / Window::GetDim().x * m_Size);
				else
					return Vector::Vec2f((float)Window::GetDim().x / Window::GetDim().y * m_Size, m_Size);
			}
		};

		class PerspectiveCamera
		{
		private:
			Vector::Vec3f m_Pos;
			
			Vector::Vec3f m_Dir;
			Vector::Vec3f m_Up;
			Vector::Vec3f m_Right;

			float m_XZAngle;
			float m_YAngle;
			float m_FoV;
			Vector::Vec2f m_ZRange;
			float m_ProjMat[4][4] = { 0 };
			float m_ViewMat[3][3] = { 0 };
		public:
			PerspectiveCamera(Vector::Vec3f pos, Vector::Vec3f dir, float foV, Vector::Vec2f zRange)
				: m_Pos(pos), m_Dir(dir), m_FoV(foV), m_ZRange(zRange)
			{
				m_YAngle = asinf(m_Dir.y);
				m_XZAngle = asinf(m_Dir.z / cosf(m_YAngle));
				float viewConstant = 1.0f / tanf(0.5f * foV);
				m_ProjMat[0][0] = viewConstant;
				m_ProjMat[1][1] = (float)Window::GetDim().x / Window::GetDim().y * viewConstant;
				m_ProjMat[2][2] = -(zRange.a + zRange.b) / (zRange.b - zRange.a);
				m_ProjMat[2][3] = -(2 * zRange.a * zRange.b) / (zRange.b - zRange.a);
				m_ProjMat[3][2] = -1;
				UpdateNormals();
				UpdateViewMat();
			}

			void RotateRight(float rotation)
			{
				m_XZAngle -= rotation;
				m_XZAngle -= (m_XZAngle > 2 * Vector::c_Pi) ? 2 * Vector::c_Pi : 0;
				m_XZAngle += (m_XZAngle < -2 * Vector::c_Pi) ? 2 * Vector::c_Pi : 0;
				UpdateNormals();
				UpdateViewMat();
			}

			void RotateUp(float rotation)
			{
				if (m_YAngle + rotation >= Vector::c_Pi / 2)
					return;
				else if (m_YAngle + rotation <= -Vector::c_Pi / 2)
					return;
			
				m_YAngle += rotation;
				UpdateNormals();
				UpdateViewMat();
			}
			void SetPosition(Vector::Vec3f pos) { m_Pos = pos; }
			void SetPosition(float x, float y, float z) { m_Pos = Vector::Vec3f(x, y, z); }

			Vector::Vec3f GetPosition() const { return m_Pos; }

			Vector::Vec3f GetDirection() const { return m_Dir; }
			Vector::Vec3f GetDirectionUp() const { return m_Up; }
			Vector::Vec3f GetDirectionRight() const { return m_Right; }

			float GetXZAngle() const { return m_XZAngle; }
			float GetYAngle() const { return m_YAngle; }

			float* GetViewMat() const { return (float*)m_ViewMat; }
			float* GetProjMat() const { return (float*)m_ProjMat; }
		private:
			void UpdateNormals()
			{
				float sinYAngle = sinf(m_YAngle);
				float cosYAngle = cosf(m_YAngle);
				float sinXZAngle = sinf(m_XZAngle);
				float cosXZAngle = cosf(m_XZAngle);

				m_Dir.x = cosXZAngle * cosYAngle;
				m_Dir.y = sinYAngle;
				m_Dir.z = sinXZAngle * cosYAngle;

				m_Right.x = sinXZAngle;
				m_Right.y = 0.0f;
				m_Right.z = -cosXZAngle;
			
				m_Up.x = -cosXZAngle * sinYAngle;
				m_Up.y = cosYAngle;
				m_Up.z = -sinXZAngle * sinYAngle;
			}
			
			void UpdateViewMat()
			{
				m_ViewMat[0][0] = m_Right.x;
				m_ViewMat[0][1] = m_Right.y;
				m_ViewMat[0][2] = m_Right.z;
				
				m_ViewMat[1][0] = m_Up.x;
				m_ViewMat[1][1] = m_Up.y;
				m_ViewMat[1][2] = m_Up.z;
				
				m_ViewMat[2][0] = -m_Dir.x;
				m_ViewMat[2][1] = -m_Dir.y;
				m_ViewMat[2][2] = -m_Dir.z;
			}
		};

		class FlatQuad
		{
		private:
			Vector::Vec3f m_Pos;
			Vector::Vec2f m_Dim;
			Vector::Vec4f m_Color;
		public:
			FlatQuad(Vector::Vec3f pos, Vector::Vec2f dim, Vector::Vec4f color = Vector::Vec4f(1.0f))
				: m_Pos(pos), m_Dim(dim), m_Color(color) {}
			FlatQuad()
				: m_Pos(), m_Dim(), m_Color(1.0f) {}

			Vector::Vec3f GetPosition() const { return m_Pos; }
			Vector::Vec2f GetDimension() const { return m_Dim; }
			Vector::Vec4f GetColor() const { return m_Color; }

			void SetPosition(Vector::Vec3f pos) { m_Pos = pos; }
			void SetPosition(float x, float y, float z) { m_Pos = Vector::Vec3f(x, y, z); }
			void SetPosition(Vector::Vec2f pos) { m_Pos = Vector::Vec3f(pos, 0); }
			void SetPosition(float x, float y) { m_Pos = Vector::Vec3f(x, y, 0); }

			void SetDimension(Vector::Vec2f dim) { m_Dim = dim; }
			void SetDimension(float x, float y) { m_Dim = Vector::Vec2f(x, y); }
			void SetDimension(float size) { m_Dim = Vector::Vec2f(size); }

			void SetColor(Vector::Vec4f color) { m_Color = color; }
			void SetColor(float r, float g, float b, float a) { m_Color = Vector::Vec4f(r, g, b, a); }
			void SetColor(Vector::Vec3f color) { m_Color = Vector::Vec4f(color, 1.0f); }
			void SetColor(float r, float g, float b) { m_Color = Vector::Vec4f(r, g, b, 1.0f); }
			void SetColor(float brightness) { m_Color = Vector::Vec4f(Vector::Vec3f(brightness), 1.0f); }
		};

		class TexQuad
		{
		private:
			Vector::Vec3f m_Pos;
			Vector::Vec2f m_Dim;
			Vector::Vec4f m_Color;
			const Texture* m_Tex;
		public:
			TexQuad(Vector::Vec3f pos, Vector::Vec2f dim, const Texture& tex, Vector::Vec4f color = Vector::Vec4f(1.0f))
				: m_Pos(pos), m_Dim(dim), m_Color(color), m_Tex(&tex) {}
			TexQuad(const FlatQuad& flat, const Texture& tex)
				: m_Pos(flat.GetPosition()), m_Dim(flat.GetDimension()), m_Color(flat.GetColor()), m_Tex(&tex) {}
			TexQuad()
				: m_Pos(), m_Dim(), m_Color(1.0f), m_Tex(nullptr) {}
			Vector::Vec3f GetPosition() const { return m_Pos; }
			Vector::Vec2f GetDimension() const { return m_Dim; }
			Vector::Vec4f GetColor() const { return m_Color; }

			void SetPosition(Vector::Vec3f pos) { m_Pos = pos; }
			void SetPosition(float x, float y, float z) { m_Pos = Vector::Vec3f(x, y, z); }
			void SetPosition(Vector::Vec2f pos) { m_Pos = Vector::Vec3f(pos, 0); }
			void SetPosition(float x, float y) { m_Pos = Vector::Vec3f(x, y, 0); }

			void SetDimension(Vector::Vec2f dim) { m_Dim = dim; }
			void SetDimension(float x, float y) { m_Dim = Vector::Vec2f(x, y); }
			void SetDimension(float size) { m_Dim = Vector::Vec2f(size); }

			void SetColor(Vector::Vec4f color) { m_Color = color; }
			void SetColor(float r, float g, float b, float a) { m_Color = Vector::Vec4f(r, g, b, a); }
			void SetColor(Vector::Vec3f color) { m_Color = Vector::Vec4f(color, 1.0f); }
			void SetColor(float r, float g, float b) { m_Color = Vector::Vec4f(r, g, b, 1.0f); }
			void SetColor(float brightness) { m_Color = Vector::Vec4f(Vector::Vec3f(brightness), 1.0f); }

			const Texture& GetTexture() const { return *m_Tex; }
			void SetTexture(const Texture& tex) { m_Tex = &tex; }
		};
	}
}