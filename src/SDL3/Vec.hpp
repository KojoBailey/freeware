#ifndef KOJO_SDL3_VEC_HPP
#define KOJO_SDL3_VEC_HPP

#include <cstddef>

namespace sdl {

template<typename T, std::size_t N> struct Vec;

template<typename T>
struct Vec<T, 2> {
	T x, y;

	auto operator+=(const Vec<T, 2>& rhs) -> Vec<T, 2>&
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	friend auto operator+(Vec<T, 2> lhs, const Vec<T, 2>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	auto operator-=(const Vec<T, 2>& rhs) -> Vec<T, 2>&
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	friend auto operator-(Vec<T, 2> lhs, const Vec<T, 2>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	auto operator*=(const T& rhs) -> Vec<T, 2>&
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	friend auto operator*(Vec<T, 2> lhs, const T& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	auto operator/=(const T& rhs) -> Vec<T, 2>&
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	friend auto operator/(Vec<T, 2> lhs, const T& rhs)
	{
		lhs /= rhs;
		return lhs;
	}
};

template<typename T> struct Vec<T, 3> { T x, y, z; };
template<typename T> struct Vec<T, 4> { T w, x, y, z; };

}

#endif
