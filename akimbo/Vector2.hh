#ifndef VECTOR2_HEADER
#define VECTOR2_HEADER

#include <cstddef>
#include <cmath>

namespace Akimbo
{

template <typename T>
struct Vector2
{
	T x;
	T y;

	Vector2() : x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}

	bool operator!=(const Vector2 <T>& rhs) const { return x != rhs.x || y != rhs.y; }
	bool operator==(const Vector2 <T>& rhs) const { return x == rhs.x && y == rhs.y; }

	/*	FIXME
	 *	The logical AND operator doesn't seem correct here */
	bool operator<=(const Vector2 <T>& rhs) const { return x <= rhs.x && y <= rhs.y; }
	bool operator>=(const Vector2 <T>& rhs) const { return x >= rhs.x && y >= rhs.y; }
	bool operator<(const Vector2 <T>& rhs) const { return x < rhs.x && y < rhs.y; }
	bool operator>(const Vector2 <T>& rhs) const { return x > rhs.x && y > rhs.y; }

	template <typename V> Vector2 <T> operator/(const Vector2 <V>& rhs) const { return Vector2 <T> (x / rhs.x, y / rhs.y); }
	template <typename V> Vector2 <T> operator*(const Vector2 <V>& rhs) const { return Vector2 <T> (x * rhs.x, y * rhs.y); }
	template <typename V> Vector2 <T> operator+(const Vector2 <V>& rhs) const { return Vector2 <T> (x + rhs.x, y + rhs.y); }
	template <typename V> Vector2 <T> operator-(const Vector2 <V>& rhs) const { return Vector2 <T> (x - rhs.x, y - rhs.y); }

	Vector2 <T> operator/(const T rhs) const { return Vector2 <T> (x / rhs, y / rhs); }
	Vector2 <T> operator*(const T rhs) const { return Vector2 <T> (x * rhs, y * rhs); }

	template <typename V> Vector2 <T> operator*=(const Vector2 <V>& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
	template <typename V> Vector2 <T> operator/=(const Vector2 <V>& rhs) { x /= rhs.x; y /= rhs.y; return *this; }
	template <typename V> Vector2 <T> operator+=(const Vector2 <V>& rhs) { x += rhs.x; y += rhs.y; return *this; }
	template <typename V> Vector2 <T> operator-=(const Vector2 <V>& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

	template <typename N>
	Vector2 <N> as() const { return Vector2 <N> (static_cast <N> (x), static_cast <N> (y)); }
	Vector2 <T> abs() const { return Vector2 <T> (std::abs(x), std::abs(y)); }
};

}

typedef Akimbo::Vector2 <float> Vec2;
typedef Akimbo::Vector2 <size_t> Vec2s;
typedef Akimbo::Vector2 <int> Vec2i;

#endif
