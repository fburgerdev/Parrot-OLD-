#pragma once
#include <iostream>

namespace Parrot
{
	namespace Math
	{
		template<class T>
		struct Vector2
		{
		public:
			union
			{
				struct { T a, b; };
				struct { T x, y; };
			};

			Vector2(const Vector2<T>& other)
				: x(other.x), y(other.y) {};
			Vector2(T x, T y)
				: x(x), y(y) {}
			Vector2(T scalar)
				: x(scalar), y(scalar) {}
			Vector2()
				: x(0), y(0) {}
			void operator=(const Vector2<T>& other) { x = other.x; y = other.y; }

			template<class T2> operator Vector2<T2>() const { return Vector2<T2>((T2)x, (T2)y); }

			T& operator[](uint8_t index) { if (index == 0) return x; else return y; }

			Vector2<T> operator-() const { return Vector2<T>(-x, -y); };
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

			void Zeros() { x = 0; y = 0; }
			inline T LengthSquared() const { return x * x + y * y; }
			inline T Length() const { return sqrt(LengthSquared()); }
			void Normalize() { T length = Length(); x /= length; y /= length; }

			inline bool operator==(const Vector2<T>& other) { return x == other.x && y == other.y; }
			inline bool operator!=(const Vector2<T>& other) { return x != other.x || y != other.y; }
			inline bool operator<(const Vector2<T>& other) { return x < other.x&& y < other.y; }
			inline bool operator>(const Vector2<T>& other) { return x > other.x && y > other.y; }
			inline bool operator<=(const Vector2<T>& other) { return x <= other.x && y <= other.y; }
			inline bool operator>=(const Vector2<T>& other) { return x >= other.x && y >= other.y; }
		private:
			friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v) { stream << "Vec2(" << v.x << ", " << v.y << ')'; return stream; }
		};

		template<class T>
		struct Vector3
		{
		public:
			union
			{
				struct { T x, y, z; };
				struct { T r, g, b; };

				struct { Vector2<T> rg; T b; };
				struct { Vector2<T> xy; T z; };

				struct { T x; Vector2<T> yz; };
				struct { T r; Vector2<T> gb; };
			};

			Vector3(const Vector3<T>& other)
				: x(other.x), y(other.y), z(other.z) {};
			Vector3(const Vector2<T>& xy, T z)
				: x(xy.x), y(xy.y), z(z) {}
			Vector3(T x, const Vector2<T>& yz)
				: x(x), y(yz.x), z(yz.y) {}
			Vector3(T x, T y, T z)
				: x(x), y(y), z(z) {}
			Vector3(T scalar)
				: x(scalar), y(scalar), z(scalar) {}
			Vector3()
				: x(0), y(0), z(0) {}
			void operator=(const Vector3<T>& other) { x = other.x; y = other.y; z = other.z; }

			template<class T2> operator Vector3<T2>() const { return Vector3<T2>((T2)x, (T2)y, (T2)z); }

			T& operator[](uint8_t index) { if (index == 0) return x; else if (index == 1)return y; else return z; }

			Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); };
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

			void Zeros() { x = 0; y = 0; z = 0; }
			inline T LengthSquared() const { return x * x + y * y + z * z; }
			inline T Length() const { return sqrt(LengthSquared()); }
			void Normalize() { T length = Length(); x /= length; y /= length; z /= length; }

			inline bool operator==(const Vector3<T>& other) { return x == other.x && y == other.y && z == other.z; }
			inline bool operator!=(const Vector3<T>& other) { return x != other.x || y != other.y || z != other.z; }
			inline bool operator<(const Vector3<T>& other) { return x < other.x && y < other.y&& z < other.z; }
			inline bool operator>(const Vector3<T>& other) { return x > other.x && y > other.y && z > other.z; }
			inline bool operator<=(const Vector3<T>& other) { return x <= other.x && y <= other.y && z <= other.z; }
			inline bool operator>=(const Vector3<T>& other) { return x >= other.x && y >= other.y && z >= other.z; }
		private:
			friend std::ostream& operator<<(std::ostream& stream, const Vector3<T>& v) { stream << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ')'; return stream; }
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

			Vector4(const Vector4<T>& other)
				: x(other.x), y(other.y), z(other.z), w(other.w) {};
			Vector4(const Vector3<T>& xyz, T w)
				: x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
			Vector4(T x, const Vector3<T>& yzw)
				: x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}
			Vector4(const Vector2<T>& xy, const Vector2<T>& zw)
				: xy(xy), zw(zw) {}
			Vector4(T x, const Vector2<T>& yz, T w)
				: x(x), y(yz.x), z(yz.y), w(w) {}
			Vector4(T x, T y, T z, T w)
				: x(x), y(y), z(z), w(w) {}
			Vector4(T scalar)
				: x(scalar), y(scalar), z(scalar), w(scalar) {}
			Vector4()
				: x(), y(), z(), w() {}
			void operator=(const Vector4<T>& other) { x = other.x; y = other.y; z = other.z; w = other.w; }

			template<class T2> operator Vector4<T2>() const { return Vector4<T2>((T2)x, (T2)y, (T2)z, (T2)w); }

			T& operator[](uint8_t index) { if (index == 0) return x; else if (index == 1)return y; else if (index == 2) return z; else return w; }

			Vector4<T> operator-() const { return Vector4<T>(-x, -y, -z, -w); };
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

			void Zeros() { x = 0; y = 0; z = 0, w = 0; }
			inline T LengthSquared() const { return x * x + y * y + z * z + w * w; }
			inline T Length() const { return sqrt(LengthSquared()); }
			void Normalize() { T length = Length(); x /= length; y /= length; z /= length; w /= length; }

			inline bool operator==(const Vector4<T>& other) { return x == other.x && y == other.y && z == other.z && w == other.w; }
			inline bool operator!=(const Vector4<T>& other) { return x != other.x || y != other.y || z != other.z || w != other.w; }
			inline bool operator<(const Vector4<T>& other) { return x < other.x&& y < other.y&& z < other.z&& w < other.w; }
			inline bool operator>(const Vector4<T>& other) { return x > other.x && y > other.y && z > other.z && w > other.w; }
			inline bool operator<=(const Vector4<T>& other) { return x <= other.x && y <= other.y && z <= other.z && w <= other.w; }
			inline bool operator>=(const Vector4<T>& other) { return x >= other.x && y >= other.y && z >= other.z && w >= other.w; }
		private:
			friend std::ostream& operator<<(std::ostream& stream, const Vector4<T>& v) { stream << "Vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')'; return stream; }
		};

		template<class T>
		Vector2<T> Normalized(const Vector2<T>& vector) { Vector2<T> output(vector); output.Normalize(); return output; }
		template<class T>
		Vector3<T> Normalized(const Vector3<T>& vector) { Vector3<T> output(vector); output.Normalize(); return output; }
		template<class T>
		Vector4<T> Normalized(const Vector4<T>& vector) { Vector4<T> output(vector); output.Normalize(); return output; }

		template<class T>
		Vector3<T> CrossProduct(const Vector3<T>& v1, const Vector3<T>& v2) { return Vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }

		template<class T>
		T DotProduct(const Vector2<T>& v1, const Vector2<T>& v2) { return v1.x * v2.x + v1.y * v2.y; }
		template<class T>
		T DotProduct(const Vector3<T>& v1, const Vector3<T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
		template<class T>
		T DotProduct(const Vector4<T>& v1, const Vector4<T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }

		typedef Vector2<int32_t> Vec2i;
		typedef Vector3<int32_t> Vec3i;
		typedef Vector4<int32_t> Vec4i;

		typedef Vector2<uint32_t> Vec2u;
		typedef Vector3<uint32_t> Vec3u;
		typedef Vector4<uint32_t> Vec4u;

		typedef Vector2<float> Vec2f;
		typedef Vector3<float> Vec3f;
		typedef Vector4<float> Vec4f;

		typedef Vector2<double> Vec2d;
		typedef Vector3<double> Vec3d;
		typedef Vector4<double> Vec4d;
	}
}