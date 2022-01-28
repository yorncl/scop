#ifndef MAT4_HPP
#define MAT4_HPP

#include <stdlib.h>
#include <iostream>

// 4 by 3 matrix in column-major representation
class Mat4
{
	private:
		float _data[16];

	public:

		Mat4();
		Mat4(const Mat4& m);
		Mat4(float value);
		~Mat4();

		float* data(); // TODO should it return a const object

		static Mat4 new_identity();
		static Mat4 new_scale(float x, float y, float z);
		static Mat4 new_translate(float x, float y, float z);
		static Mat4 new_rotation();
		static Mat4 new_projection();

		Mat4& operator=(const Mat4& m);
		friend Mat4 operator*(const Mat4& m, float f); // scalar multiplication
		friend Mat4 operator*(const Mat4& m1, const Mat4& m2); // scalar multiplication
		float* operator[](size_t i);
		const float* operator[](size_t i) const;
		friend std::ostream& operator<<(std::ostream &os, const Mat4&);
};

#endif
