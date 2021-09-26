#pragma once
#include <iostream>
#include <math.h>

namespace Parrot
{
	namespace Vector
	{
		// Quake square root
		static float QuakeInverseSquareRoot(float number)
		{
			long i;
			float y;

			y = number;
			i = *(long*)&y;
			i = 0x5f3759df - (i >> 1);
			y = *(float*)&i;
			y = y * (1.5F - (number * 0.5F * y * y));

			return y;
		}

		static float QuakeSquareRoot(float number)
		{
			QuakeInverseSquareRoot(number * number);
		}

		//Structs---------------------------------------------------------------------------------------------------------------
		template<class T>
		struct Vector2
		{
		public:
			union
			{
				struct { T a, b; };
				struct { T x, y; };
			};

			// Assignment
			Vector2(const Vector2<T>& other)
				: x(other.x), y(other.y) {};
			Vector2(T x, T y)
				: x(x), y(y) {}
			Vector2(T scalar)
				: x(scalar), y(scalar) {}
			Vector2()
				: x(), y() {}
			void operator=(const Vector2<T>& other) { x = other.x; y = other.y; }

			// Cast
			template<class T2> operator Vector2<T2>() const { return Vector2<T2>((T2)x, (T2)y); }

			// Accessing
			T& operator[](uint8_t index) { if (index == 0) return x; else return y; }

			// Arithmetic operators
			void operator+=(const Vector2<T>& other) { x += other.x, y += other.y; }
			void operator-=(const Vector2<T>& other) { x -= other.x, y -= other.y; }
			Vector2<T> operator+(const Vector2<T>& other) const { return Vector2<T>(x + other.x, y + other.y); }
			Vector2<T> operator-(const Vector2<T>& other) const { return Vector2<T>(x - other.x, y - other.y); };
			void operator*=(T scalar) { x *= scalar; y *= scalar; }
			void operator/=(T scalar) { x /= scalar; y /= scalar; }
			Vector2<T> operator*(T scalar) const { return Vector2<T>(x * scalar, y * scalar); }
			Vector2<T> operator/(T scalar) const { return Vector2<T>(x / scalar, y / scalar); }
			void operator*=(const Vector2<T>& other) { x *= other.x; y *= other.y; }
			void operator/=(const Vector2<T>& other) { x /= other.x; y /= other.y; }
			Vector2<T> operator*(const Vector2<T>& other) const { return Vector2<T>(x * other.x, y * other.y); }
			Vector2<T> operator/(const Vector2<T>& other) const { return Vector2<T>(x / other.x, y / other.y); }

			// Advanced arithmetic
			void Zeros() { x = 0; y = 0; }
			inline double LengthSquared() const { return x * x + y * y; }
			inline double Length() const { return sqrt(LengthSquared()); }
			inline float LengthFast() const { return QuakeSquareRoot(LengthSquared); }
			void Normalize() { double length = Length(); x /= length; y /= length; }
			void NormalizeFast() { float inv = QuakeInverseSquareRoot(LengthSquared()); x *= inv; y *= inv; }

			// Comparison
			inline bool operator==(const Vector2<T>& other) { return x == other.x && y == other.y; }
			inline bool operator!=(const Vector2<T>& other) { return x != other.x || y != other.y; }
			inline bool operator<(const Vector2<T>& other) { return x < other.x && y < other.y; }
			inline bool operator>(const Vector2<T>& other) { return x > other.x && y > other.y; }
			inline bool operator<=(const Vector2<T>& other) { return x <= other.x && y <= other.y; }
			inline bool operator>=(const Vector2<T>& other) { return x >= other.x && y >= other.y; }

			// Debugging
			void Print() const { std::cout << x << ',' << y << std::endl; }
		};

		template<class T>
		struct Vector3
		{
		public:
			union
			{
				struct { T x, y, z; };
				struct { T r, g, b; };

				struct { Vector2<T> xy; T z; };
				struct { Vector2<T> rg; T b; };

				struct { T x; Vector2<T> yz; };
				struct { T r; Vector2<T> gb; };
			};

			// Assignment
			Vector3(const Vector3<T>& other)
				: x(other.x), y(other.y), z(other.z) {};
			Vector3(const Vector2<T>& xy, T z)
				: xy(xy), z(z) {}
			Vector3(T x, const Vector2<T>& yz)
				: x(x), yz(yz) {}
			Vector3(T x, T y, T z)
				: x(x), y(y), z(z) {}
			Vector3(T scalar)
				: x(scalar), y(scalar), z(scalar) {}
			Vector3()
				: x(), y(), z() {}
			void operator=(const Vector3<T>& other) { x = other.x; y = other.y; z = other.z; }

			// Cast
			template<class T2> operator Vector3<T2>() const { return Vector3<T2>((T2)x, (T2)y, (T2)z); }

			// Accessing
			T& operator[](uint8_t index) { if (index == 0) return x; else if (index == 1)return y; else return z; }

			// Arithmetic operators
			void operator+=(const Vector3<T>& other) { x += other.x, y += other.y; z += other.z; }
			void operator-=(const Vector3<T>& other) { x -= other.x, y -= other.y; z -= other.z; }
			Vector3<T> operator+(const Vector3<T>& other) const { return Vector3<T>(x + other.x, y + other.y, z + other.z); }
			Vector3<T> operator-(const Vector3<T>& other) const { return Vector3<T>(x - other.x, y - other.y, z - other.z); };
			void operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; }
			void operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; }
			Vector3<T> operator*(T scalar) const { return Vector3<T>(x * scalar, y * scalar, z * scalar); }
			Vector3<T> operator/(T scalar) const { return Vector3<T>(x / scalar, y / scalar, z / scalar); }
			void operator*=(const Vector3<T>& other) { x *= other.x; y *= other.y; z *= other.z; }
			void operator/=(const Vector3<T>& other) { x /= other.x; y /= other.y; z /= other.z; }
			Vector3<T> operator*(const Vector3<T>& other) const { return Vector3<T>(x * other.x, y * other.y, z * other.z); }
			Vector3<T> operator/(const Vector3<T>& other) const { return Vector3<T>(x / other.x, y / other.y, z / other.z); }

			// Advanced arithmetic
			void Zeros() { x = 0; y = 0; z = 0; }
			inline double LengthSquared() const { return x * x + y * y + z * z; }
			inline double Length() const { return sqrt(LengthSquared()); }
			inline float LengthFast() const { return QuakeSquareRoot(LengthSquared); }
			void Normalize() { double length = Length(); x /= length; y /= length; z /= length; }
			void NormalizeFast() { float inv = QuakeInverseSquareRoot(LengthSquared()); x *= inv; y *= inv; z *= inv; }

			// Comparison
			inline bool operator==(const Vector3<T>& other) { return x == other.x && y == other.y && z == other.z; }
			inline bool operator!=(const Vector3<T>& other) { return x != other.x || y != other.y || z != other.z; }
			inline bool operator<(const Vector3<T>& other) { return x < other.x && y < other.y && z < other.z; }
			inline bool operator>(const Vector3<T>& other) { return x > other.x && y > other.y && z > other.z; }
			inline bool operator<=(const Vector3<T>& other) { return x <= other.x && y <= other.y && z <= other.z; }
			inline bool operator>=(const Vector3<T>& other) { return x >= other.x && y >= other.y && z >= other.z; }

			// Debugging
			void Print() const { std::cout << x << ',' << y << ',' << z << std::endl; }
		};

		template<class T>
		struct Vector4
		{
		public:
			union
			{
				struct { T x, y, z, w; };
				struct { T r, g, b, a; };

				struct { Vector2<T> xy, zw; };
				struct { Vector2<T> rg, ba; };

				struct { T x; Vector2<T> yz; T w; };
				struct { T r; Vector2<T> gb; T a; };

				struct { Vector3<T> xyz; T w; };
				struct { Vector3<T> rgb; T a; };

				struct { T x;  Vector3<T> yzw; };
				struct { T r;  Vector3<T> gba; };
			};

			// Assignment
			Vector4(const Vector4<T>& other)
				: x(other.x), y(other.y), z(other.z), w(other.w) {};
			Vector4(const Vector3<T>& xyz, T w)
				: xyz(xyz), w(w) {}
			Vector4(T x, const Vector3<T>& yzw)
				: x(x), yzw(yzw) {}
			Vector4(const Vector2<T>& xy, const Vector2<T>& zw)
				: xy(xy), zw(zw) {}
			Vector4(T x, const Vector2<T>& yz, T w)
				: x(x), yz(yz), w(w) {}
			Vector4(T x, T y, T z, T w)
				: x(x), y(y), z(z), w(w) {}
			Vector4(T scalar)
				: x(scalar), y(scalar), z(scalar), w(scalar) {}
			Vector4()
				: x(), y(), z(), w() {}
			void operator=(const Vector4<T>& other) { x = other.x; y = other.y; z = other.z; w = other.w; }

			// Cast
			template<class T2> operator Vector4<T2>() const { return Vector4<T2>((T2)x, (T2)y, (T2)z, (T2)w); }

			// Accessing
			T& operator[](uint8_t index) { if (index == 0) return x; else if (index == 1)return y; else if (index == 2) return z; else return w; }

			// Arithmetic operators
			void operator+=(const Vector4<T>& other) { x += other.x, y += other.y; z += other.z; w += other.w; }
			void operator-=(const Vector4<T>& other) { x -= other.x, y -= other.y; z -= other.z; w -= other.w; }
			Vector4<T> operator+(const Vector4<T>& other) const { return Vector4<T>(x + other.x, y + other.y, z + other.z, w + other.w); }
			Vector4<T> operator-(const Vector4<T>& other) const { return Vector4<T>(x - other.x, y - other.y, z - other.z, w - other.w); };
			void operator*=(T scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; }
			void operator/=(T scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; }
			Vector4<T> operator*(T scalar) const { return Vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar); }
			Vector4<T> operator/(T scalar) const { return Vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar); }
			void operator*=(const Vector4<T>& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; }
			void operator/=(const Vector4<T>& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; }
			Vector4<T> operator*(const Vector4<T>& other) const { return Vector4<T>(x * other.x, y * other.y, z * other.z, w * other.w); }
			Vector4<T> operator/(const Vector4<T>& other) const { return Vector4<T>(x / other.x, y / other.y, z / other.z, w / other.w); }

			// Advanced arithmetic
			void Zeros() { x = 0; y = 0; z = 0, w = 0; }
			inline double LengthSquared() const { return x * x + y * y + z * z + w * w; }
			inline double Length() const { return sqrt(LengthSquared()); }
			inline float LengthFast() const { return QuakeSquareRoot(LengthSquared); }
			void Normalize() { double length = Length(); x /= length; y /= length; z /= length; w /= length; }
			void NormalizeFast() { float inv = QuakeInverseSquareRoot(LengthSquared()); x *= inv; y *= inv; z *= inv; w *= inv; }

			// Comparison
			inline bool operator==(const Vector4<T>& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
			inline bool operator!=(const Vector4<T>& other) { return x != other.x || y != other.y || z != other.z || w != other.w; }
			inline bool operator<(const Vector4<T>& other) { return x < other.x && y < other.y && z < other.z && w < other.w; }
			inline bool operator>(const Vector4<T>& other) { return x > other.x && y > other.y && z > other.z && w > other.w; }
			inline bool operator<=(const Vector4<T>& other) { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
			inline bool operator>=(const Vector4<T>& other) { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }

			// Debugging
			void Print() const { std::cout << x << ',' << y << ',' << z << ',' << w << std::endl; }
		};

		// Vector methods-------------------------------------------------------------------------------------------------------
		// Normalized
		template<class T>
		Vector2<T> Normalized(const Vector2<T>& vector)
		{
			Vector2<T> output(vector);
			output.Normalize();
			return output;
		}

		template<class T>
		Vector3<T> Normalized(const Vector3<T>& vector)
		{
			Vector3<T> output(vector);
			output.Normalize();
			return output;
		}

		template<class T>
		Vector4<T> Normalized(const Vector4<T>& vector)
		{
			Vector4<T> output(vector);
			output.Normalize();
			return output;
		}

		// CrossProduct
		template<class T>
		Vector3<T> CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return Vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
		}

		// DotProduct
		template<class T>
		T DotProduct(const Vector2<T>& v1, const Vector2<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
		template<class T>
		T DotProduct(const Vector3<T>& v1, const Vector3<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}
		template<class T>
		T DotProduct(const Vector4<T>& v1, const Vector4<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
		}

		// Typedefs-------------------------------------------------------------------------------------------------------------
		typedef Vector2<int32_t> Vec2i;
		typedef Vector3<int32_t> Vec3i;
		typedef Vector4<int32_t> Vec4i;

		typedef Vector2<int8_t> Vec2i_8;
		typedef Vector3<int8_t> Vec3i_8;
		typedef Vector4<int8_t> Vec4i_8;

		typedef Vector2<uint32_t> Vec2u;
		typedef Vector3<uint32_t> Vec3u;
		typedef Vector4<uint32_t> Vec4u;

		typedef Vector2<uint8_t> Vec2u_8;
		typedef Vector3<uint8_t> Vec3u_8;
		typedef Vector4<uint8_t> Vec4u_8;

		typedef Vector2<double> Vec2d;
		typedef Vector3<double> Vec3d;
		typedef Vector4<double> Vec4d;

		typedef Vector2<float> Vec2f;
		typedef Vector3<float> Vec3f;
		typedef Vector4<float> Vec4f;
	}
}