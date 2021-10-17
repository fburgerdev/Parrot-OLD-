#include <immintrin.h>
#include <memory>

namespace Math
{
	struct Vec2fNew
	{
	private:
		__m128 reg128;
	public:
		union
		{
			struct { float x, y; };
			struct { float a, b; };
		};

		Vec2fNew(float val)
			: x(val), y(val) {}
		Vec2fNew(float x, float y)
			: x(x), y(y) {}
		
		Vec2fNew operator+(const Vec2fNew& other) { __m128 = _mm256_set_p}
	};
}