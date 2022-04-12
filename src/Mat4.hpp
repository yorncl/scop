#ifndef MAT4_HPP
#define MAT4_HPP

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cmath>

// 4 by 4 matrix in column-major representation
template <typename T>
class Mat4
{
	private:
		T _data[16];

	public:

		Mat4()
		{
			memset(_data, 0, sizeof(T) * 16);
		}

		Mat4(T value)
		{
			for (size_t i = 0; i < 16; i++)
				_data[i] = value;
		}


		Mat4(const Mat4& m)
		{
			for (size_t i = 0; i < 16; i++)
				_data[i] = m._data[i];
		}

		~Mat4()
		{
		}

		T* data()
		{
			return _data;
		}

		const T* data() const
		{
			return _data;
		}

		static Mat4 new_identity()
		{
			Mat4 m;
			m[0][0] = 1.0f; 
			m[1][1] = 1.0f; 
			m[2][2] = 1.0f; 
			m[3][3] = 1.0f; 
			return m;
		}

		static Mat4 new_scale(T x, T y, T z)
		{
			Mat4 m;
			m[0][0] = x; 
			m[1][1] = y; 
			m[2][2] = z; 
			m[3][3] = 1.0f; 
			return m;
		}

		static Mat4 new_translate(T x, T y, T z)
		{
			Mat4 m = new_identity();
			m[3][0] = x; 
			m[3][1] = y; 
			m[3][2] = z; 
			return m;
		}

		static Mat4 new_rotation(T x, T y, T z)
		{
			Mat4 m;

			m[0][0] = cos(x) * cos(y); 
			m[0][1] = sin(x) * cos(y); 
			m[0][2] = -sin(y); 

			m[1][0] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z); 
			m[1][1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z); 
			m[1][2] = cos(y) * sin(z); 

			m[2][0] = cos(x) * sin(y) * cos(z) + sin(x) * sin(z); 
			m[2][1] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z); 
			m[2][2] = cos(y) * cos(z); 

			m[3][3] = 1; 
			return m;
		}

		static Mat4 new_projection(double fovx, double aspratio)
		{
			 T n = 0.1;
			 T f = -100;

			 T hx = tan((fovx/2) * (M_PI /180)) * n;
			 T hy = hx / aspratio; 

			 T r = hx;
			 T l = -r;

			 T t = hy;
			 T b = -t;

			// in column-major order, this is the protjection matrix
			// 2 * n / ( r - l ), 	0.0, 	 	 	0.0, 		0.0, 
			// 0.0, 		2 * n / ( t- b), 	0.0, 		0.0, 
			// (r + l) / (r -l ), 	(t + b)/ (t-b), 	-(f+n)/(f-n), 	-1, 
			// 0.0, 		0.0, 			-2*f*n/(f-n), 	0.0
			
			Mat4 m;
			m[0][0] = 2 * n/ (r - l);
			m[1][1] = 2 * n/ (t - b);

			m[2][0] = (r + l) / (r - l);
			m[2][1] = (t + b) / (t - l);
			m[2][2] = -(f + n) / (f - n);
			m[2][3] = -1;

			m[3][2] = - 2 * f * n / (f - n);

			return m;
		}

		Mat4& operator=(const Mat4& m)
		{
			for (size_t i = 0; i < 16; i++)
				_data[i] = m._data[i];
			return *this;
		}

		T* operator[](size_t i)
		{
			return &_data[i * 4];
		}

		const T* operator[](size_t i) const
		{
			return &_data[i * 4];
		}

	template <typename U>
	friend Mat4<U> operator*(const Mat4<U>& m, U f);
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const Mat4<T>& m)
{
	os << "Mat4 :" << std::endl;
	for(size_t i = 0; i < 4; i++)
	{
		for(size_t j = 0; j < 4; j++)
			os << m[j][i] << ' ';
		os << std::endl;
	}
	os << "Raw Mat4: " << std::endl;
	const T* data = m.data();
	for (size_t i = 0; i < 16; i++)
		std::cout << data[i];
	os << std::endl;
	return os;
}

template <typename T>
Mat4<T> operator*(const Mat4<T>& m, T f)
{
	Mat4<T> r;
	for (size_t i = 0; i < 16; i++)
		r._data[i] = m._data[i] * f;
	return r;
}

template <typename T>
Mat4<T> operator*(T f, const Mat4<T>& m)
{
	return m * f;
}

template <typename T>
Mat4<T> operator*(const Mat4<T>& m1, const Mat4<T>& m2)
{
	Mat4<T> r;
	for (size_t j = 0; j < 4; j++)
	{
		for (size_t i = 0; i < 4; i++)
			r[j][i] = m1[0][i] * m2[j][0] + m1[1][i] * m2[j][1] + m1[2][i] * m2[j][2] + m1[3][i] * m2[j][3];
	}
	return r;
}

#endif
