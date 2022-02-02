#ifndef VEC3_HPP
#define VEC3_HPP

#include <type_traits>
#include <math.h>

// Basic template class for 3 dimensional vector

#pragma pack (push, 1)
template<typename T>
class Vec3
{
	public:
	T x;
	T y;
	T z;

	Vec3(){}
	Vec3(T a, T b, T c): x(a), y(b), z(c){}
	Vec3(const Vec3& v){x=v.x; y=v.y; z=v.z;}
	~Vec3(){}

	Vec3 cross(const Vec3& v)
	{
		return Vec3(
				y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x
				);
	}

	Vec3& operator=(const Vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	void normalize()
	{
		T norm = sqrt(x*x + y*y + z*z);
		if (norm != 0)
		{
			x /= norm;
			y /= norm;
			z /= norm;
		}
	}

	template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
	Vec3 operator*(U scalar)
	{
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

	template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
	Vec3 operator+(U scalar)
	{
		return Vec3(x + scalar, y + scalar, z + scalar);
	}

	template <typename U, typename = typename std::enable_if<std::is_arithmetic<U>::value, U>::type>
	Vec3 operator-(U scalar)
	{
		return Vec3(x - scalar, y - scalar, z - scalar);
	}

	Vec3 operator+(Vec3& v)
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator-(Vec3& v)
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
};
#pragma pack(pop)

#endif
