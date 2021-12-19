#pragma once
#include "Constants.hpp"
#include "Vector.hpp"

#include <assert.h>

namespace Parrot
{
	namespace Math
	{
		template<class T, size_t Dim>
		class SqrMat
		{
		public:
			SqrMat() { memset(m_Data, 0, sizeof(T) * Dim * Dim); }
			SqrMat(const T* data) { memcpy(m_Data, data, sizeof(T) * Dim * Dim); }
			SqrMat(const SqrMat<T, Dim>& other) { memcpy(m_Data, other.m_Data, sizeof(T) * Dim * Dim); }

			void Zeros() { memset(m_Data, 0, sizeof(T) * Dim * Dim); }
			void Identity() { Zeros(); for (size_t i = 0; i < Dim; ++i) m_Data[i + Dim * i] = 1; }
			const T* Raw() const { return m_Data; }
			void Transpose()
			{
				for (size_t i = 0; i < Dim; ++i)
				{
					for (size_t j = i; j < Dim; ++j)
					{
						T temp = m_Data[Dim * j + i];
						m_Data[Dim * j + i] = m_Data[Dim * i + j];
						m_Data[Dim * i + j] = temp;
					}
				}
			}

			T* operator[](uint64_t index) { return m_Data + Dim * index; }
			void operator+=(const SqrMat<T, Dim>& other)
			{
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] += other.m_Data[i];
			}
			void operator-=(const SqrMat<T, Dim>& other)
			{
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] -= other.m_Data[i];
			}
			SqrMat<T, Dim> operator+(const SqrMat<T, Dim>& other) const
			{
				SqrMat<T, Dim> out(m_Data);
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] += other.m_Data[i];
				return out;
			}
			SqrMat<T, Dim> operator-(const SqrMat<T, Dim>& other) const
			{
				SqrMat<T, Dim> out(m_Data);
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] -= other.m_Data[i];
				return out;
			}
			void operator*=(float scalar)
			{
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] *= scalar;
			}
			SqrMat<T, Dim> operator*(float scalar) const
			{
				SqrMat<T, Dim> out(m_Data);
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] *= scalar;
				return out;
			}
			void operator*=(double scalar)
			{
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] *= scalar;
			}
			SqrMat<T, Dim> operator*(double scalar) const
			{
				SqrMat<T, Dim> out(m_Data);
				for (size_t i = 0; i < Dim * Dim; ++i)
					m_Data[i] *= scalar;
				return out;
			}
			SqrMat<T, Dim> operator*(const SqrMat<T, Dim>& other) const
			{
				SqrMat<T, Dim> out;
				for (size_t row = 0; row < Dim; ++row)
					for (size_t col = 0; col < Dim; ++col)
						for (size_t i = 0; i < Dim; ++i)
							out.m_Data[row * Dim + col] += m_Data[i * Dim + col] * other.m_Data[row * Dim + i];
				return out;
			}

			Math::Vector2<T> operator*(const Math::Vector2<T>& vec) const
			{
				static_assert(Dim == 2, "You can only multiply a Vec2f with a Mat2");
				return Math::Vector2<T>(m_Data[0] * vec.x + m_Data[2] * vec.y, m_Data[1] * vec.x + m_Data[4] * vec.y);
			}
			Math::Vector3<T> operator*(const Math::Vector3<T>& vec) const
			{
				static_assert(Dim == 3, "You can only multiply a Vec3 with a Mat3");
				return Math::Vector3<T>(m_Data[0] * vec.x + m_Data[3] * vec.y + m_Data[6] * vec.z,
										m_Data[1] * vec.x + m_Data[4] * vec.y + m_Data[7] * vec.z,
										m_Data[2] * vec.x + m_Data[5] * vec.y + m_Data[8] * vec.z);
			}
			Math::Vector4<T> operator*(const Math::Vector4<T>& vec) const
			{
				static_assert(Dim == 4, "You can only multiply a Vec4 with a Mat4");
				return Math::Vector4<T>(m_Data[0] * vec.x + m_Data[4] * vec.y + m_Data[8] * vec.z + m_Data[12] * vec.w,
										m_Data[1] * vec.x + m_Data[5] * vec.y + m_Data[9] * vec.z + m_Data[13] * vec.w,
										m_Data[2] * vec.x + m_Data[6] * vec.y + m_Data[10] * vec.z + m_Data[14] * vec.w,
										m_Data[3] * vec.x + m_Data[7] * vec.y + m_Data[11] * vec.z + m_Data[15] * vec.w);
			}
		private:
			T m_Data[Dim * Dim];
		};

		template<class T, size_t Dim >
		SqrMat<T, Dim> Transposed(const SqrMat<T, Dim>& mat)
		{
			SqrMat<T, Dim> out(mat);
			out.Transpose();
			return out;
		}

		// yaw pitch roll Euler rotation
		template<class T>
		SqrMat<T, 4> RotationMat(const Math::Vector3<T>& rot)
		{
			T sina = sin(rot.z);
			T cosa = cos(rot.z);
			T sinb = sin(rot.x);
			T cosb = cos(rot.x);
			T sinc = sin(rot.y);
			T cosc = cos(rot.y);

			SqrMat<T, 4> out;
			out[0][0] = cosa * cosb;
			out[0][1] = sina * cosb;
			out[0][2] = -sinb;

			out[1][0] = cosa * sinb * sinc - sina * cosc;
			out[1][1] = sina * sinb * sinc + cosa * cosc;
			out[1][2] = cosb * sinc;

			out[2][0] = cosa * sinb * cosc + sina * sinc;
			out[2][1] = sina * sinb * cosc - cosa * sinc;
			out[2][2] = cosb * cosc;

			out[3][3] = 1;

			return out;
		}
		template<class T>
		SqrMat<T, 4>&  Translate(SqrMat<T, 4>& mat, const Math::Vector3<T>& translation)
		{
			memcpy(mat[3], &translation, sizeof(T) * 3);
			return mat;
		}
		template<class T>
		SqrMat<T, 4>& Scale(SqrMat<T, 4>& mat, const Math::Vector3<T>& scaling)
		{
			mat[0][0] *= scaling.x;
			mat[0][1] *= scaling.x;
			mat[0][2] *= scaling.x;

			mat[1][0] *= scaling.y;
			mat[1][1] *= scaling.y;
			mat[1][2] *= scaling.y;

			mat[2][0] *= scaling.z;
			mat[2][1] *= scaling.z;
			mat[2][2] *= scaling.z;
			return mat;
		}
		template<class T>
		SqrMat<T, 4>& Rotate(Math::SqrMat<T, 4>&mat, const Math::Vector3<T>& rot)
		{
			mat = RotationMat(rot) * mat;
			return mat;
		}
		template<class T>
		Math::Vector3<T> Rotate(const Math::Vector3<T>& vec, const Math::Vector3<T>& rot)
		{				
			return RotationMat(rot) * vec;
		}
		
		typedef SqrMat<int32_t, 2> Mat2i;
		typedef SqrMat<int32_t, 3> Mat3i;
		typedef SqrMat<int32_t, 4> Mat4i;
		
		typedef SqrMat<uint32_t, 2> Mat2u;
		typedef SqrMat<uint32_t, 3> Mat3u;
		typedef SqrMat<uint32_t, 4> Mat4u;

		typedef SqrMat<float, 2> Mat2f;
		typedef SqrMat<float, 3> Mat3f;
		typedef SqrMat<float, 4> Mat4f;

		typedef SqrMat<double, 2> Mat2d;
		typedef SqrMat<double, 3> Mat3d;
		typedef SqrMat<double, 4> Mat4d;
	}
}