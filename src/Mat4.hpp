#ifndef MAT4_HPP
#define MAT4_HPP

#include <stdlib.h>

class Mat4
{
	private:
		float _data[16];

	public:

		Mat4();
		Mat4(const Mat4& m);
		Mat4(float value);
		~Mat4();

		static Mat4 new_identity();
		static Mat4 new_scale(float x, float y, float z);
		static Mat4 new_translate(float x, float y, float z);
		static Mat4 new_rotation();
		static Mat4 new_projection();

		Mat4& operator=(Mat4& m);
		float* operator[](size_t i);
};

#endif
