#include "Forge/Math/TF_Type.h"

struct TFloat2;

//----------------------------------------------------------------------------
// TFloat2
//----------------------------------------------------------------------------
// A simple structure containing 2 floating point values.
// TFloat2 is always guaranteed to be 2 floats in size. Only use when a very
// specific size is required (like defining structures that need to be the
// same across platforms, or the same on CPU and GPU (like constant and
// structured buffers) In all other cases you should opt to use Vector2, since
// it uses SIMD optimizations whenever possible. TFloat2 does not.
//----------------------------------------------------------------------------
struct TFloat2 
{
	TFloat2()								 : TFloat2(0, 0) {}
	constexpr TFloat2(float x, float y)       : x(x), y(y) {}
	constexpr TFloat2(int32_t x, int32_t y)   : x((float)x), y((float)y) {}
	constexpr TFloat2(uint32_t x, uint32_t y) : x((float)x), y((float)y) {}
	constexpr TFloat2(int64_t x, int64_t y)   : x((float)x), y((float)y) {}
	constexpr TFloat2(uint64_t x, uint64_t y) : x((float)x), y((float)y) {}
	constexpr explicit TFloat2(float x)       : x(x), y(x) {}
	constexpr explicit TFloat2(int32_t x)     : x((float)x), y((float)x) {}
	constexpr explicit TFloat2(uint32_t  x)   : x((float)x), y((float)x) {}
	constexpr explicit TFloat2(int64_t x)     : x((float)x), y((float)x) {}
	constexpr explicit TFloat2(uint64_t  x)   : x((float)x), y((float)x) {}
	constexpr TFloat2(const TFloat2& f)        : x(f.x), y(f.y) {}
	constexpr TFloat2(const float(&fv)[2])    : x(fv[0]), y(fv[1]){}

	float& operator[](int i) { return (&x)[i]; }
	float operator[](int i) const { return (&x)[i]; }

	float getX() const { return x; }
	float getY() const { return y; }

	void setX(float x_) { x = x_; }
	void setY(float y_) { y = y_; }

	float x, y;
};

inline TFloat2 operator+(const TFloat2& a, const TFloat2& b) { return TFloat2(a.x + b.x, a.y + b.y); }
inline TFloat2 operator-(const TFloat2& a, const TFloat2& b) { return TFloat2(a.x - b.x, a.y - b.y); }
inline TFloat2 operator-(const TFloat2& a) { return TFloat2(-a.x, -a.y); }
inline TFloat2 operator*(const TFloat2& a, float b) { return TFloat2(a.x * b, a.y * b); }
inline TFloat2 operator*(float a, const TFloat2& b) { return b * a; }
inline TFloat2 operator*(const TFloat2& a, const TFloat2& b) { return TFloat2(a.x * b.x, a.y * b.y); }
inline TFloat2 operator/(const TFloat2& a, float b) { return TFloat2(a.x / b, a.y / b); }
inline TFloat2 operator/(float a, const TFloat2& b) { return b / a; }
inline TFloat2 operator/(const TFloat2& a, const TFloat2& b) { return TFloat2(a.x / b.x, a.y / b.y); }

inline const TFloat2& operator+=(TFloat2& a, const TFloat2& b) { return a = a + b; }
inline const TFloat2& operator-=(TFloat2& a, const TFloat2& b) { return a = a - b; }
inline const TFloat2& operator*=(TFloat2&a, float b) { return a = a * b; }
inline const TFloat2& operator*=(TFloat2&a, TFloat2& b) { return a = a * b; }
inline const TFloat2& operator/=(TFloat2& a, float b) { return a = a / b; }
inline const TFloat2& operator/=(TFloat2&a, const TFloat2& b) { return a = a / b; }

inline bool operator==(const TFloat2 &a, const TFloat2 &b)
{
    return ((a.x - b.x < FLT_EPSILON && a.x - b.x > -FLT_EPSILON) &&
            (a.y - b.y < FLT_EPSILON && a.y - b.y > -FLT_EPSILON));
}
inline bool operator!=(const TFloat2 &a, const TFloat2 &b)
{
    return !(a == b);
}


//----------------------------------------------------------------------------
// TFloat3
//----------------------------------------------------------------------------
// A simple structure containing 3 floating point values.
// TFloat3 is always guaranteed to be 3 floats in size. Only use when a very
// specific size is required (like defining structures that need to be the
// same across platforms, or the same on CPU and GPU (like constant and
// structured buffers) In all other cases you should opt to use Vector3, since
// it uses SIMD optimizations whenever possible. TFloat3 does not.
//----------------------------------------------------------------------------
struct TFloat3
{
	TFloat3()											 : TFloat3(0, 0, 0) {}
	constexpr TFloat3(float x, float y, float z)          : x(x), y(y), z(z) {}
	constexpr TFloat3(int32_t x, int32_t y, int32_t z)    : x((float)x), y((float)y), z((float)z) {}
	constexpr TFloat3(uint32_t x, uint32_t y, uint32_t z) : x((float)x), y((float)y), z((float)z) {}
	constexpr TFloat3(int64_t x, int64_t y, int64_t z)    : x((float)x), y((float)y), z((float)z) {}
	constexpr TFloat3(uint64_t x, uint64_t y, uint64_t z) : x((float)x), y((float)y), z((float)z) {}
	constexpr explicit TFloat3(float x)                   : x(x), y(x), z(x) {}
	constexpr explicit TFloat3(int32_t x)                 : x((float)x), y((float)x), z((float)x) {}
	constexpr explicit TFloat3(uint32_t x)                : x((float)x), y((float)x), z((float)x) {}
	constexpr explicit TFloat3(int64_t x)                 : x((float)x), y((float)x), z((float)x) {}
	constexpr explicit TFloat3(uint64_t x)                : x((float)x), y((float)x), z((float)x) {}
	constexpr TFloat3(const TFloat3& f)                    : x(f.x), y(f.y), z(f.z) {}
	constexpr TFloat3(const float(&fv)[3])                : x(fv[0]), y(fv[1]), z(fv[2]) {}

	float& operator[](int i) { return (&x)[i]; }
	float operator[](int i) const { return (&x)[i]; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	TFloat2 getXY() const { return TFloat2(x, y); }

	void setX(float x_) { x = x_; }
	void setY(float y_) { y = y_; }
	void setZ(float z_) { z = z_; }

	float x, y, z;
};

inline TFloat3 operator+(const TFloat3& a, const TFloat3& b) { return TFloat3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline TFloat3 operator-(const TFloat3& a, const TFloat3& b) { return TFloat3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline TFloat3 operator-(const TFloat3& a) { return TFloat3(-a.x, -a.y, -a.z); }
inline TFloat3 operator*(const TFloat3& a, float b) { return TFloat3(a.x * b, a.y * b, a.z * b); }
inline TFloat3 operator*(float a, const TFloat3& b) { return b * a; }
inline TFloat3 operator*(const TFloat3& a, const TFloat3& b) { return TFloat3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline TFloat3 operator/(const TFloat3& a, float b) { return TFloat3(a.x / b, a.y / b, a.z / b); }
inline TFloat3 operator/(float a, const TFloat3& b) { return b / a; }
inline TFloat3 operator/(const TFloat3& a, const TFloat3& b) { return TFloat3(a.x / b.x, a.y / b.y, a.z / b.z); }

inline const TFloat3& operator+=(TFloat3& a, const TFloat3& b) { return a = a + b; }
inline const TFloat3& operator-=(TFloat3& a, const TFloat3& b) { return a = a - b; }
inline const TFloat3& operator*=(TFloat3&a, float b) { return a = a * b; }
inline const TFloat3& operator*=(TFloat3&a, TFloat3& b) { return a = a * b; }
inline const TFloat3& operator/=(TFloat3& a, float b) { return a = a / b; }
inline const TFloat3& operator/=(TFloat3&a, const TFloat3& b) { return a = a / b; }

inline bool operator==(const TFloat3 &a, const TFloat3 &b)
{
    return ((a.x - b.x < FLT_EPSILON && a.x - b.x > -FLT_EPSILON) &&
            (a.y - b.y < FLT_EPSILON && a.y - b.y > -FLT_EPSILON) &&
            (a.z - b.z < FLT_EPSILON && a.z - b.z > -FLT_EPSILON));
}
inline bool operator!=(const TFloat3 &a, const TFloat3 &b)
{
    return !(a == b);
}
